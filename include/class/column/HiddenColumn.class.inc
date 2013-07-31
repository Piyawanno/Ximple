<?php
require_once('CharColumn.class.inc');
class HiddenColumn extends CharColumn{
	function HiddenColumn($default, $type){
		$this->isConfigFormAllowed = false;
		$this->setType($type);
		$this->defaultData = $default;
		$this->data = $default;
		$this->setFormAttribute('type', 'hidden');
		$this->isFormLabel = false;
	}
	
	public function renderForm($formID){
		if(empty($this->data)) $this->data = $this->defaultData;
		return CharColumn::renderForm($formID);
	}
	
	public function renderGridForm($formID){
		if(empty($this->data)) $this->data = $this->defaultData;
		return CharColumn::renderGridForm($formID);
	}
}
?>
