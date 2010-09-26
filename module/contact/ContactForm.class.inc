<?php
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include('ContactFormModel.class.inc');

class ContactForm extends ConfigControl{
	function ContactForm($contactID, $contactName){
		$this->moduleTitle = $contactName;
		$this->init(new ContactFormModel($contactID));
	}
	
	public function render($description){
		$this->formMeta->id = 'contact';
		$this->formMeta->description = $description;
		$this->formMeta->mode = 'contact_send';
		$this->formMeta->title = $this->moduleTitle;
		$this->formMeta->isCaptcha = true;
		return ConfigControl::render();
	}
	
	protected function getConfig(){
	}
}
?>
