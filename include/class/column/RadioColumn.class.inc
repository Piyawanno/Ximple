<?php
require_once('SelectiveColumn.class.inc');
class RadioColumn extends SelectiveColumn{
	public function renderForm($formID){
		$this->listClass = 'radio_list';
		$this->setFormAtrribute('type', 'radio');
		$this->setFormAtrribute('name', $this->name);
		return SelectiveForm::renderRawsForm($formID);
	}
	
	protected function getCheck($data){
		if($data != $this->data) $this->setFormAtrribute('checked', '');
		else $this->setFormAtrribute('checked', 'checked');
	}
}
?>
