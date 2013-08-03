<?php
require_once('CharColumn.class.inc');
class AutoCompleteColumn extends CharColumn{
	public $useComma = true;
	private static $globalUseComma = array();
	private $ajaxMode;
	
	function AutoCompleteColumn($label, $ajaxMode, $help=null){
		CharColumn::CharColumn($label, $help);
		$this->ajaxMode = $ajaxMode;
	}
	
	public function triggerGetJavaScript(){
		head_add_js('include/javascript/autocomplete.column.js');
	}
	
	public function renderForm($formID){
		$this->globalUseComma[$this->name] = $this->useComma;
		head_add_js_array('autoCompleteUseCommaColumn', $this->globalUseComma);
		$this->setFormAttribute('alt', $this->ajaxMode);
		$this->setFormAttribute('class', 'auto_complete');
		return CharColumn::renderForm($formID);
	}
	
	public function renderGridForm($formID){
		$this->globalUseComma[$this->name.'[]'] = $this->useComma;
		head_add_js_array('autoCompleteUseCommaColumn', $this->globalUseComma);
		$this->setFormAttribute('alt', $this->ajaxMode);
		$this->setFormAttribute('class', 'auto_complete');
		return CharColumn::renderGridForm($formID);
	}
}
?>
