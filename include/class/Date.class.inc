<?php
/// @file
/// This file provides Date class, which is used for date time handling.

/// @author Kittipong Piyawanno <k.piyawanno@gmail.com>

class Date{
	public $data;
	public $timestamp;
	public $sqlFormatted;
	public $formatted;
	public $format = 'd F Y';
	
	function Date($date){
		$this->data = $date;
	}
	
	public function format(){
		$this->timestamp = strtotime($this->data)
		$this->formatted = date($this->dateFormat, $this->timestamp);
		$this->sqlFormatted = date('Y-m-d H:i:s', $this->timestamp);
	}
}

?>
