<?php
require_once(ROOT_PATH.'include/class/ModelFactory.class.inc');
require_once(ROOT_PATH.'include/class/ModelConnector.class.inc');

/// This class is a container for other ModelColumns.
/// It does not represent a column of database table.
class GridColumn extends ModelColumn{
	public $hasDBRow = false;
	public $memberColumn;
	public $dropMode;
	
	private $id = null;
	private $dataModifier = null;
	private $memberDataCount;
	private $modelConnector;
	private $tableName;
	private $relatedDataModifier;
	private $insertData;
	private $updateData;
	
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
		$this->setType('array');
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
	
	public function append($name, $memberModel){
		$this->setColumn($name, $memberModel);
	}
	
	public function renderForm($formID){
		require_once(ROOT_PATH.'include/class/GridFormRender.class.inc');
		$this->getMember();
		$formRender = new GridFormRender();
		$formRender->setGridColumn($this);
		return $formRender->renderForm($formID);
	}
	
	public function triggerUpdateForm(){
		
	}
	
	public function triggerPostDBInsert(){
		if($this->hasDBRow){
			print_r(pp());
			print_r(ff());
#			$this->initDataModifier();
#			$this->modelConnector->triggerSetParent();
#			$this->dataModifier->prepareInsert();
#			$this->dataModifier->insert(false);
		}
	}
	
	public function triggerPostDBUpdate(){
		if($this->hasDBRow){
			$this->initDataModifier();
			$this->modelConnector->triggerSetParent();
			$this->separateData();
			
			$this->dataModifier->prepareInsert();
			$this->dataModifier->insert(false);
			
#			$this->dataModifier->prepareUpdate();
#			$this->dataModifier->update(false);
		}
	}
	
	public function triggerGetID($id){
		$this->id = $id;
		$this->modelConnector->setParentID($id);
	}
	
	private function getMember(){
		if($this->hasDBRow and !empty($this->id)){
			$this->getMemberDBData();
		}else{
			$this->checkMemberData();
			$this->getMemberData();
		}
		return $this->memberColumn;
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
	
	private function getMemberDBData(){
		$clause = 'WHERE '.$this->parentColumn.'='.$this->id;
		$column = $this->modelConnector->getColumnName();
		$member = $this->memberColumn;
		$this->data = db_select($this->tableName, $column, $clause);
		foreach($this->data as $id => $data){
			foreach($data as $column => $value){
				if(isset($member[$column])  and $member[$column]->isGridForm){
					$this->memberColumn[$column]->data = $value;
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
				$columnModel->name = $key;
				$this->setColumn($value, $columnModel);
			}
		}
	}
	
	private function setColumn($name, $memberModel){
		$memberModel->isMultipleInsert = true;
		$memberModel->name = $name;
		if($memberModel->isGridForm){
			$memberModel->type = 'array';
		}
		$memberModel->isForm = false;
		$this->memberColumn[$name] = $memberModel;
	}
	
	private function initDataModifier(){
		if(!$this->dataModifier){
			include_once('DataModifier.class.inc');
			$this->dataModifier = new DataModifier($this->tableName, $this->modelConnector);
		}
	}
	
	private function separateData(){
		
	}
}
?>
