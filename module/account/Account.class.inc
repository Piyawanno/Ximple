<?php
require_once(ROOT_PATH.'module/user/User.class.inc');
execute_add_class('account', 'Account');

class Account extends User{
	public function Account(){
		$this->tableName = 'users';
		$this->moduleName = 'account';
		$this->setAdmin('user_admin');
		$this->initNotification();
		$this->init(new UserModel());
	}
	
	public function index(){
		document_set_path(tt('Configure Account'));
		$this->getUID();
		$this->selectByID($this->column, true);
		return $this->renderForm();
	}
	
	public function update(){
		$this->prepareModifyDB();
		User::update();
		$accountDirectory = ROOT_PATH.'files/account/';
		if(!is_dir($accountDirectory)) mkdir($accountDirectory);
		$config = pp();
		$config['signature'] = strip_tags($config['signature']);
		io_serialize($config, $accountDirectory.USER_ID);
		document_set_redirect('account');
		notify_add_info(tt('Your account configuration has been successfully updated.'));
	}
	
	private function renderForm(){
		$additionalForm = $this->renderAdditionForm();
		$this->initJS();
		head_add_js_var('insertUser', false);
		head_add_js_var('uid', gg('id'));
		$this->moduleTitle = sprintf(tt('Account Configuration : %s'), $this->dataByID['login_name']);
		$this->formMeta->id = 'user';
		$this->formMeta->title = $this->moduleTitle;
		$this->formMeta->mode = 'account_update';
		$this->formMeta->additionalForm = $additionalForm;
		$this->renderAvatar();
		return $this->renderUpdateForm();
	}
	
	private function renderAdditionForm(){
		$form = array($this->renderConfigForm());
		$additional = cc('account_config');
		if(is_array($additional)){
			foreach($additional as $key => $value){
				$form[] = execute_string($value);
			}
		}
		return $form;
	}
	
	private function renderConfigForm(){
		include_once(ROOT_PATH.'include/class/QuickFormRender.class.inc');
		$formRender = new QuickFormRender('user');
		
		$signature = Model::char(tt('signature'));
		$signature->data = uu('signature');
		
		$language = Model::select(tt('default language for my user interface'), translate_get_interface_language());
		$language->data = uu('language');
		
		$permissionSelect = $this->getProfilePermissionOption();
		$profile = Model::radio(tt('who can see my profile'), $permissionSelect);
		$profile->data = uu('profile_permission');
		
		$email = Model::radio(tt('who can send me an email'), $permissionSelect);
		$email->data = uu('email_permission');
	
		$formRender->append('signature', $signature);
		$formRender->append('language', $language);
		$formRender->append('profile_permission', $profile);
		$formRender->append('email_permission', $email);
		return $formRender->render();
	}
	
	private function getUID(){
		$modeID = mid();
		if($modeID != 0) $this->id = $modeID;
		else $this->id = USER_ID;
	}
	
	private function getProfilePermissionOption(){
		return array(
			0 => tt('Everybody included anonymous visitor'),
			1 => tt('All authenticated users'),
			2 => tt('Only you and administration'),
		);
	}
}
?>
