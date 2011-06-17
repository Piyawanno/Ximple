<?php
require_once(MODULE_PATH.'user/User.class.inc');
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
		$this->getUID();
		User::update(false);
		$accountDirectory = FILES_PATH.'account/';
		if(!is_dir($accountDirectory)) mkdir($accountDirectory);
		$config = pp();
		$config['uid'] = $this->id;
		$config['signature'] = strip_tags($config['signature']);
		
		if(isset($config['subscribe'])) $this->updateSubscriber($config['subscribe']);
		else $this->updateSubscriber(array());
		
		$config = extension_execute('account_update', $config, $config);
		io_serialize($config, $accountDirectory.$this->id);
		document_set_redirect('account');
		notify_add_info(tt('Your account configuration has been successfully updated.'));
		document_set_redirect('account/'.$this->id);
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
		include_once(INCLUDE_PATH.'class/QuickFormRender.class.inc');
		$formRender = new QuickFormRender('user');
		
		$signature = Model::char(tt('signature'));
		$signature->data = user_info_get_config($this->id, 'signature');
		
		$language = Model::select(tt('default language for my user interface'), translate_get_interface_language());
		$language->data = user_info_get_config($this->id, 'language');
		
		$subscribeOption = $this->getSubcribeOption();
		$subscribe = Model::checkbox(tt('send me an email by'), $subscribeOption);
		$subscribe->data = user_info_get_config($this->id, 'subscribe');
		
		$permissionOption = $this->getProfilePermissionOption();
		$profile = Model::radio(tt('who can see my profile'), $permissionOption);
		$profile->data = user_info_get_config($this->id, 'profile_permission');
		
		$email = Model::radio(tt('who can send me an email'), $permissionOption);
		$email->data = user_info_get_config($this->id, 'email_permission');
	
		$formRender->append('signature', $signature);
		$formRender->append('language', $language);
		$formRender->append('subscribe', $subscribe);
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
	
	private function getSubcribeOption(){
		$configSubscribe = cc('subscribable_module');
		if(!is_array($configSubscribe)) $configSubscribe = array();
		$option = array(
			'comment' => tt('someone comments on my contributions'),
		);
		return array_merge($option, $configSubscribe);
	}
	
	private function updateSubscriber($subscribe){
		$subscribeDir = $this->createSubcribeDirectory();
		$this->addSubscriber($subscribe, $subscribeDir);
		$this->dropSubscriber($subscribe, $subscribeDir);
	}
	
	private function addSubscriber($subscribe, $subscribeDir){
		foreach($subscribe as $key => $value){
			$subscriber = io_unserialize($subscribeDir.$value);
			if(!is_array($subscriber)) $subscriber = array();
			if(!isset($subscriber[$this->id])){
				$subscriber[$this->id] = true;
				io_serialize($subscriber, $subscribeDir.$value);
			}
		}
	}
	
	private function dropSubscriber($subscribe, $subscribeDir){
		$configSubscribe = cc('subscribable_module');
		foreach($configSubscribe  as $key => $value){
			if(!in_array($key, $subscribe)){
				$subscriber = io_unserialize($subscribeDir.$key);
				unset($subscriber[$this->id]);
				io_serialize($subscriber, $subscribeDir.$key);
			}
		}
	}
	
	private function createSubcribeDirectory(){
		$subscribeDir = FILES_PATH.'subscribe/';
		if(!is_dir($subscribeDir)) mkdir($subscribeDir);
		return $subscribeDir;
	}
}
?>
