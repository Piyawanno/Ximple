<?php
require_once(ROOT_PATH.'module/user/User.class.inc');
require_once('TutorRegistrationModel.class.inc');

class TutorRegistration extends User{
	function TutorRegistration(){
		$this->tableName = 'users';
		$this->moduleName = 'triamsob';
		$this->setAdmin('user_admin');
		$this->insertNotify = sprintf(tt('%s has been successfully inserted.'), tt('User'));
		$this->updateNotify = sprintf(tt('%s has been successfully updated.'), tt('User'));
		$this->dropNotify = sprintf(tt('%s has been successfully dropped.'), tt('User'));
		$this->init(new TutorRegistrationModel());
	}
	
	public function registration(){
		$this->initJS();
		head_add_js_var('insertUser', true);
		$this->moduleTitle = tt('Tutor Registration');
		$this->formMeta->id = 'user';
		$this->formMeta->title = $this->moduleTitle;
		$this->formMeta->mode = 'triamsob_tutor_registration_save';
		$description = io_read_file(ROOT_PATH.'module/triamsob/registration.txt');
		$description = str_replace("\n", '<br />', $description);
		$this->formMeta->description = $description;
		$this->formMeta->isCaptcha = true;
		return $this->renderInsertForm();
	}
}
?>
