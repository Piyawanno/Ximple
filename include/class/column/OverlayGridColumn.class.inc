<?php
class OverlayGridColumn extends ModelColumn{
	private $childControl;
	
	function OverlayGridColumn($label, $help=null){
		$this->setType('array');
		$this->help = $help;
		$this->label = $label;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
	}
	
	public function setChildControl($control){
		$this->childControl = $control;
	}
	
	public function renderForm($formID){
		require_once(ROOT_PATH.'include/class/OverlayGridFormRender.class.inc');
		$formRender = new OverlayGridFormRender();
		return $formRender->renderForm($formID);
	}
}
?>
