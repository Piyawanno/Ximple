<?php
require_once('CharColumn.class.inc');
class AutoCompleteColumn extends CharColumn{
	private $ajaxMode;
	
	function AutoCompleteColumn($label, $ajaxMode, $help=null){
		CharColumn::CharColumn($label, $help);
		$this->ajaxMode = $ajaxMode;
	}
	
	public function renderForm($formID){
		head_add_js('include/javascript/autocomplete.column.js');
		$this->setFormAttribute('alt', $this->ajaxMode);
		$this->setFormAttribute('class', 'auto_complete');
		return CharColumn::renderForm($formID);
	}
}
?>
