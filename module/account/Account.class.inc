<?php
require_once(MODULE_PATH.'user/User.class.inc');
execute_add_class('account', 'Account');

class Account extends User{
	private $additionConfigForm = array();
	
	public function Account(){
		$this->tableName = 'users';
		$this->moduleName = 'account';
		$this->setAdmin('user_admin');
		$this->initNotification();
		$this->updateMap = false;
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
		
		$config = extension_execute('account_update', $config);
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
		$this->renderConfigForm();
		$this->formMeta->additionalForm = $additionalForm;
		$this->renderAvatar();
		return $this->renderUpdateForm();
	}
	
	private function renderAdditionForm(){
		$form = array();
		$additional = cc('account_config');
		if(is_array($additional)){
			foreach($additional as $key => $value){
				$form[] = execute_string($value);
			}
		}
		return $form;
	}
	
	private function renderConfigForm(){
		require_once(INCLUDE_PATH.'class/ConfigFormRender.class.inc');
		require_once('AccountConfigModel.class.inc');
		$label = tt('Generic Configuration');
		$generic = new ConfigFormRender($label, $this->modelConnector);
		$generic->appendModel('generic', new AccountConfigModel($this->id));
		$this->configForm[] = $generic;
	}
	
	private function getUID(){
		$modeID = mid();
		if($modeID != 0) $this->id = $modeID;
		else $this->id = USER_ID;
	}
	
	private function updateSubscriber($subscribe){
		$subscribeDir = notify_create_subscribe_directory();
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
		$configSubscribe = notify_get_subscribable_module();
		foreach($configSubscribe  as $key => $value){
			if(!in_array($key, $subscribe)){
				$subscriber = io_unserialize($subscribeDir.$key);
				unset($subscriber[$this->id]);
				io_serialize($subscriber, $subscribeDir.$key);
			}
		}
	}
}
?>
