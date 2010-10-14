<?php
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include('ResetPasswordModel.class.inc');

class ResetPassword extends ConfigControl{
	private $userID;
	private $fileName;
	
	function ResetPassword(){
		$this->moduleName = 'forgetpassword';
		$this->moduleTitle = tt('Reset Password');
		$this->addAction('forgetpassword_reset', 'index');
		$this->addAction('forgetpassword_reset_save', 'save');
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'save');
		$this->init(new ResetPasswordModel());
	}
	
	public function index(){
		if($this->checkKey()) return $this->renderForm();
		else $this->invalidLink();
	}
	
	public function save(){
		if($this->checkKey()){
			db_update('users', array('password' => pp('password')), $this->userID);
			unlink($this->fileName.'.php');
			execute_set_db();
			notify_add_info(tt('Your pass word has been already changed, please login.'));
		}else{
			$this->invalidLink();
		}
	}
	
	private function renderForm(){
		$this->formMeta->id = 'user';
		$this->formMeta->mode = 'forgetpassword_reset_save/file/'.gg('file').'/key/'.gg('key');
		$this->formMeta->title = $this->moduleTitle;
		head_add_js_var('insertUser', true);
		head_add_js_var('passwdTooShort', tt('Password is too short.'));
		head_add_js_var('passwdVeryStrong', tt('Password strength is very strong.'));
		head_add_js_var('passwdStrong', tt('Password strength is strong.'));
		head_add_js_var('passwdMedium', tt('Password strength is medium.'));
		head_add_js_var('passwdWeak', tt('Password strength is weak.'));
		head_add_js_var('passwdMismatch', tt('Password is mismathed.'));
		return $this->render();
	}
	
	private function checkKey(){
		if(count(split('\/\.\.', gg('filename'))) >= 2) error_denied();
		$this->fileName = ROOT_PATH.'files/forgetpassword/'.gg('file');
		$controlData = io_unserialize($this->fileName);
		if(is_array($controlData)){
			if($controlData['key'] == gg('key')){
				$this->userID = $controlData['uid'];
				return true;
			}
		}
		return false;
	}
	
	private function invalidLink(){
		notify_add_error(tt('The requested URI for password resetting is invalid.'));
		execute_set_db();
	}
}
?>
