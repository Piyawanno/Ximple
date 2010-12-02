<?php

class FormMetaData{
	public $id = '';
	public $description = '';
	public $title;
	public $mode;
	public $configForm;
	public $additionalForm = array();
	public $submitLabel;
	public $isCaptcha = false;
	public $isSetTitle = true;
	
	function FormMetaData(){
		$this->submitLabel  = tt('submit');
	}
}

?>
