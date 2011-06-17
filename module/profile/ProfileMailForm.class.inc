<?php
include_once(INCLUDE_PATH.'class/ConfigControl.class.inc');
include('ProfileMailFormModel.class.inc');

class ProfileMailForm extends ConfigControl{
	function ProfileMailForm(){
		$this->moduleTitle = sprintf(tt('Send email to %s'), gg('send_to'));
		$this->init(new ProfileMailFormModel());
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
