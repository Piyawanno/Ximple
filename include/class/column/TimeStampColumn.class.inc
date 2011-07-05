<?php
require_once('CalendarColumn.class.inc');
class TimeStampColumn extends CalendarColumn{
	public function renderForm($formID){
		$this->prepareHead();		
		$id = $formID.'_'.$this->name;
		list($date, $hour, $minute) = $this->processTimeStamp();
		$render  = $this->renderDate($id, $date).' '; 
		$render .= tt('time').' ';
		$render .= $this->renderHour($id, $hour).' : '; 
		$render .= $this->renderMinute($id, $minute); 
		$render .= '<span id="info_'.$id.'"></span>';
		return $render;
	}
	
	public function triggerPostInsert(){
		$time = pp($this->name.'_hour').':'.pp($this->name.'_minute').':00';
		$this->data = date('Y-m-d', strtotime($this->data)).' '.$time;
	}
	
	public function triggerPostUpdate(){
		$time = pp($this->name.'_hour').':'.pp($this->name.'_minute').':00';
		$this->data = date('Y-m-d', strtotime(pp($this->name))).' '.$time;
	}
	
	private function prepareHead(){
		head_add_css('include/external/jquery-spinbox/jquery.spinbox.css');
		head_add_js('include/external/jquery-spinbox/jquery.spinbox.js');
		head_add_js('include/javascript/calendar.column.js');
		head_add_js('include/javascript/timestamp.column.js');
	}
	
	private function processTimeStamp(){
		if($this->data){
			$time = strtotime($this->data);
			$date = date('d F Y', $time);
			$hour = date('H', $time);
			$minute = date('i', $time);
		}else{
			$date = date('d F Y');
			$hour = date('H');
			$minute = date('i');
		}
		return array($date, $hour, $minute);
	}
	
	private function renderDate($id, $date){
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('id', $id);
		$this->setFormAttribute('class', 'calendar_form');
		$this->setFormAttribute('value', $date);
		return '<input '.$this->renderFormAttribute().'/>';
	}
	
	
	private function renderHour($id, $hour){
		$this->setFormAttribute('id', null);
		$this->setFormAttribute('size', 3);
		$this->setFormAttribute('name', $this->name.'_hour');
		$this->setFormAttribute('class', 'timestamp_hour_form');
		$this->setFormAttribute('value', $hour);
		return '<input '.$this->renderFormAttribute().'/>';
	}
	
	private function renderMinute($id, $minute){
		$this->setFormAttribute('id', null);
		$this->setFormAttribute('size', 3);
		$this->setFormAttribute('name', $this->name.'_minute');
		$this->setFormAttribute('class', 'timestamp_minute_form');
		$this->setFormAttribute('value', $minute);
		return '<input '.$this->renderFormAttribute().'/>';
	}
}
?>
