<?php
class OverlayGridColumn extends ModelColumn{
	public $childModuleName;
	public $childTableName;
	public $parentColumn;
	
	protected $childModule;
	
	function OverlayGridColumn($label, $childModule, $help=null){
		$this->setType('array');
		$this->label = $label;
		$this->childModule = $childModule;
		$childModule->getJavaScript();
		$this->childModuleName = $childModule->fullModuleName;
		$this->childTableName = $childModule->tableName;
		$this->parentColumn = $this->childModule->getParentColumnName();
		$this->help = $help;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
		$this->isLink = true;
	}
	
	public function triggerGetJavaScript(){
		head_add_js('include/javascript/overlaygrid.column.js');
	}
	
	public function triggerPostDBInsert(){
		if($this->isLink){
			$table = $this->childModule->tableName;
			$parentColumn = $this->childModule->modelConnector->getParentColumnName();
			$inputName = 'overlay_grid_'.$table;
			$input = pp($inputName);
			foreach($input as $key => $value){
				$data = array(
					$parentColumn => $this->id,
				);
				db_update($data, $value);
			}
		}
	}
	
	public function triggerDBDrop(){
		if($this->isLink){
			$clause = 'WHERE '.$this->parentColumn.'='.$this->id;
			db_drop_many($this->childTableName, $clause);
		}
	}
	
	public function triggerGetID($id){
		$this->id = $id;
	}
	
	public function renderForm($formID){
		head_add_css('list.css');
		$renderArray = array(
			'form_id' => $formID,
			'module_name' => $this->childModuleName,
		);
		return render($renderArray, 'overlay_form.tpl', 'overlay_form');
	}
}
?>
