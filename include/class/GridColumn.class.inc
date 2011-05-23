<?php
require_once('ModelFactory.class.inc');
require_once('ModelConnector.class.inc');

/// This class is a container for other ModelColumns.
/// It does not represent a column of database table.
class GridColumn extends ModelColumn{
	public $hasDBRow = false;
	public $dropMode = '';
	
	private $id;
	private $dataModifier = null;
	private $memberColumn;
	private $memberDataCount;
	private $modelConnector;
	private $tableName;
	private $relatedDataModifier;
	
	private $allowedGridForm = array(
		'none',
		'hidden',
		'char',
		'autocomplete',
		'calendar',
		'email',
		'select',
		'file',
	);
	
	function GridColumn($label, $help=null){
		$this->type = 'array';
		$this->form = 'grid';
		$this->help = $help;
		$this->label = $label;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
	}
	
	public function setModel($modelObj){
		$this->tableName = $modelObj->tableName;
		$this->dropMode = $modelObj->dropMode;
		$this->hasDBRow = true;
		$this->isDB = false;
		$this->initModelConnector($modelObj->moduleName, $modelObj);
		$this->mergeModel();
		$this->parentColumn = $this->modelConnector->getParentColumnName();
		return $this;
	}
	
	public function append($memberName, $memberModel){
		if(!in_array($memberModel->form, $this->allowedGridForm)){
			if(state_is_develop()){
				notify_add_error(sprintf(tt('Grid is not allowed to contain form : %s.'), $memberModel->form));
			}
		}else{
			$this->setColumn($memberName, $memberModel);
		}
	}
	
	public function getMember(){
		if($this->hasDBRow){
			$clause = 'WHERE '.$this->parentColumn.'='.$this->id;
			$column = $this->modelConnector->getColumnName();
			$this->data = db_select($this->tableName, $column, $clause);
			foreach($this->data as $id => $data){
				foreach($data as $column => $value){
					if(isset($this->memberColumn[$column]) and $this->memberColumn[$column]->isGridForm){
						$this->memberColumn[$column]->data = $value;
					}
				}
			}
		}else{
			$this->checkMemberData();
			$this->getMemberData();
		}
		return $this->memberColumn;
	}
	
	public function triggerUpdateForm(){
		
	}
	
	public function triggerPostDBInsert(){
		if($this->hasDBRow){
			$this->initDataModifier();
			$this->modelConnector->triggerSetParent();
			$this->dataModifier->prepareInsert();
			$this->dataModifier->insert(false);
		}
	}
	
	public function triggerPostDBUpdate(){
		if($this->hasDBRow){
			$this->initDataModifier();
			$this->modelConnector->triggerSetParent();
			$this->dataModifier->prepareUpdate();
			$this->dataModifier->update(false);
		}
	}
	
	public function triggerGetID($id){
		$this->id = $id;
		$this->modelConnector->setParentID($id);
	}
	
	private function checkMemberData(){
		$dataCount = array();
		$dataOK = true;
		foreach($this->memberColumn as $key => $value){
			if(is_array($value->data)){
				$dataCount[] = count($value->data);
			}else{
				$dataCount[] = null;
			}
		}
		if(count($dataCount)){
			foreach($dataCount as $key => $value){
				if($value != $dataCount[0]){
					notify_add_warning(sprintf(tt('Data for %s is corrupted!'), $this->label));
					$dataOK = false;
					break;
				}
			}
		}
		if($dataOK) $this->memberDataCount = $dataCount[0];
	}
	
	private function getMemberData(){
		$this->data = array();
		for($i=0;$i<$this->memberDataCount;$i++){
			foreach($this->memberColumn as $key => $value){
				if(is_array($value->data)){
					$this->data[$i][$key] = $value->data[$i];
				}
			}
		}
	}
	
	private function initModelConnector($moduleName, $modelObj){
		$modelFactory = new ModelFactory($moduleName, $modelObj);
		$this->modelConnector = $modelFactory->bind();
	}
	
	private function mergeModel(){
		$column = $this->modelConnector->getColumnName();
		foreach($column as $key => $value){
			$columnModel = $this->modelConnector->getColumn($value);
			if(!empty($columnModel)){
				$this->setColumn($value, $columnModel);
			}
		}
	}
	
	private function setColumn($memberName, $memberModel){
		if(in_array($memberModel->form, $this->allowedGridForm)){
			$memberModel->isMultipleInsert = true;
			if($memberModel->isGridForm){
				$memberModel->type = 'array';
			}
			$memberModel->isForm = false;
			$this->memberColumn[$memberName] = $memberModel;
		}elseif(state_is_develop()){
			notify_add_error(sprintf(tt('Invalid form for grid : %s(%s)'), $memberName, $memberModel->form));
		}
	}
	
	private function initDataModifier(){
		if(!$this->dataModifier){
			include_once('DataModifier.class.inc');
			$this->dataModifier = new DataModifier($this->tableName, $this->modelConnector);
		}
	}
}
?>
