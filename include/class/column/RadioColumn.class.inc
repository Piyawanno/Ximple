<?php
require_once('SelectiveColumn.class.inc');
class RadioColumn extends SelectiveColumn{
	public function renderForm($formID){
		$this->formClass = 'form_radio';
		$this->setFormAtrribute('type', 'radio');
		return SelectiveForm::renderRawsForm($formID);
	}
	
	protected function getCheck($data){
		if($data != $this->data) $this->setFormAtrribute('checked', '');
		else $this->setFormAtrribute('checked', 'checked');
	}
}
?>
