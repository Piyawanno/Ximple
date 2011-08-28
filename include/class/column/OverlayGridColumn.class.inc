<?php
class OverlayGridColumn extends ModelColumn{
	public $childModuleName;
	
	function OverlayGridColumn($label, $childModuleName, $help=null){
		$this->setType('array');
		$this->label = $label;
		$this->childModuleName = $childModuleName;
		$this->help = $help;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
	}
	
	public function renderForm($formID){
		head_add_js('include/javascript/overlayGrid.column.js');
		$renderArray = array(
			'form_id' => $formID,
			'module_name' => $this->childModuleName,
			'label' => $this->label,
			'help' => $this->help,
		);
		return render($renderArray, 'overlay_form.tpl', 'overlay_form');
	}
}
?>
