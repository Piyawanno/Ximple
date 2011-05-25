<?php
require_once('CharColumn.class.inc');
class CalendarColumn extends CharColumn{
	public $formatDateBySelect = false;
	public $dataFormat;
	
	function CalendarColumn($label, $help=null){
		CharColumn::CharColumn($label, $help);
		$this->data = NOW;
		$this->defaultData = NOW;
	}
	
	public function triggerSelect(){
		if($this->formatDateBySelect){
			$this->data = date($this->dataFormat, strtotime($this->data));
		}
	}
	
	public function renderForm($formID){
		head_add_js('include/javascript/calendarcolumn.js');
		if($this->data){
			$$this->data = date('d F Y', strtotime($this->data));
		}else{
			$$this->data = date('d F Y');
		}
		$this->setFormAtrribute('class', 'calendar_form');
		return CharColumn::renderForm($formID);
	}
}
?>