<?php
/// This class is a container for other ModelColumns.
/// It does not represent a column of database table.
class OverlayGridColumn extends ModelColumn{
	public $childModuleName;
	public $childTableName;
	public $parentColumn;
	
	private $id;
	private $childControl;
	private $modelConnector;
	
	function OverlayGridColumn($label, $childControl, $help=null){
		if(!is_a($childControl, 'OverlayControl') and state_is_develop()){
			notify_add_error(tt('Child Control of OverlayGridColumn should be OverlayControl.'));
		}
		$this->setType('array');
		$this->label = $label;
		$this->childControl = $childControl;
		
		$modelFactory = new ModelFactory($childControl->getModel());
		$this->modelConnector = $modelFactory->bind();
		
		$this->childModuleName = $childControl->fullModuleName;
		$this->childTableName = $childControl->tableName;
		$this->parentColumn = $this->modelConnector->getParentColumnName();
		
		$this->help = $help;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
		$this->isLink = true;
	}
	
	public function triggerGetJavaScript(){
		$this->modelConnector->triggerGetJavaScript();
		head_add_js('include/javascript/overlaygrid.column.js');
		head_add_js('include/javascript/grid.column.js');
	}
	
	public function triggerPostDBInsert(){
		if($this->isLink){
			$table = $this->childTableName;
			$inputName = 'overlay_grid_'.$table;
			$input = pp($inputName);
			if(is_array($input)){
				foreach($input as $key => $value){
					$data = array(
						$this->parentColumn => $this->id,
					);
					db_update($this->childTableName, $data, $value);
				}
			}
		}
	}
	
	public function triggerDrop(){
		if($this->isLink){
			echo('Hello');
			$control = $this->childControl;
			$clause = 'WHERE '.$this->parentColumn.'='.$this->id;
			$control->select(array('id'), $clause);
			$idArray = array_keys($control->data);
			foreach($idArray as $key => $value){
				$control->id = $value;
				$control->drop();
			}
		}
	}
	
	public function triggerGetID($id){
		$this->id = $id;
	}
	
	public function triggerSelect(){
		$clause = 'WHERE '.$this->parentColumn.'='.$this->id;
		$this->childControl->select($this->childControl->column, $clause);
		$this->data = $this->childControl->data;
	}
	
	public function renderForm($formID){
		head_add_css('list.css');
		head_add_js_var('overlayParentID', $this->id);
		$renderArray = array(
			'form_id' => $formID,
			'id' => $this->id,
			'module_name' => $this->childModuleName,
		);
		return render($renderArray, 'overlay_form.tpl', 'overlay_form');
	}
}
?>
