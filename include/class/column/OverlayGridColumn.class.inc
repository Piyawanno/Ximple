<?php
class OverlayGridColumn extends ModelColumn{
	public $childModuleName;
	
	function OverlayGridColumn($label, $childModule, $help=null){
		$this->setType('array');
		$this->label = $label;
		$childModule->getJavaScript();
		$this->childModuleName = $childModule->fullModuleName;
		$this->help = $help;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
	}
	
	public function triggerGetJavaScript(){
		head_add_js('include/javascript/overlayGrid.column.js');
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
