<?php
include(ROOT_PATH.'module/user/User.class.inc');

class Registration extends User{
	public function write(){
		$this->initJS();
		head_add_js_var('insertUser', true);
		$this->moduleTitle = tt('Registration');
		$this->formMeta->id = 'user';
		$this->formMeta->title = $this->moduleTitle;
		$this->formMeta->mode = 'registration_save';
		$this->formMeta->description = cc('registration_page');
		$this->formMeta->isCaptcha = true;
		return $this->renderInsertForm();
	} 
}
?>