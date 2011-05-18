<?php
execute_add_class('user', 'User');
include('UserModel.class.inc');

class User extends Control{
	private $groupForm;
	
	function User(){
		$this->tableName = 'users';
		$this->moduleName = 'user';
		$this->setAdmin('user_admin');
		$this->insertNotify = sprintf(tt('%s has been successfully inserted.'), tt('User'));
		$this->updateNotify = sprintf(tt('%s has been successfully updated.'), tt('User'));
		$this->dropNotify = sprintf(tt('%s has been successfully dropped.'), tt('User'));
		$this->init(new UserModel());
	}
	
	public function index(){
		$this->moduleTitle = tt('User');
		document_set_path(tt('User'), 'user');
		document_set_title(tt('User'));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->description = tt('You can use this page to manage and communicate with the users in the Section.');
		$this->listMeta->mode = 'user';
		$this->listMeta->defaultOrderDesc = 'id';
		$this->setListWriteIcon(tt('Add a new User'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		/// In the main Section, you can manage users from all Sections.
		/// In the other Section, you can manage only users in the own Sections.
		if(SECTION != 1){
			$this->selectListPage(20, "WHERE (status='active' AND section=".SECTION.")");
		}else{
			$this->selectListPage(20, "WHERE (status='active')");
		}
		return $this->renderListPage();
	}
	
	public function write(){
		$this->moduleTitle = tt('User');
		document_set_path(tt('User'), 'user');
		$this->initJS();
		head_add_js_var('insertUser', true);
		$this->injectGroupForm();
		$this->formMeta->id = $this->moduleName;
		$this->formMeta->title = tt('Add a new User');
		$this->formMeta->mode = 'user_insert';
		return $this->renderInsertForm();
	}
	
	public function insert(){
		Control::insert();
		$this->updateMap();
	}
	
	public function account($additionalForm ){
		$this->initJS();
		head_add_js_var('insertUser', false);
		head_add_js_var('uid', gg('id'));
		$this->moduleTitle = sprintf(tt('Account Configuration : %s'), $this->dataByID['login_name']);
		$this->formMeta->id = 'user';
		$this->formMeta->title = $this->moduleTitle;
		$this->formMeta->mode = 'account_save';
		$this->formMeta->additionalForm = $additionalForm;
		$this->renderAvatar();
		return $this->renderUpdateForm();
	}
	
	public function edit(){
		$this->moduleTitle = tt('User');
		document_set_path(tt('User'), 'user');
		$this->initJS();
		head_add_js_var('insertUser', false);
		head_add_js_var('uid', gg('id'));
		$this->injectGroupForm();
		$this->getGroupData();
		$this->formMeta->id = $this->moduleName;
		$this->formMeta->title = tt('Update User : ').$this->dataByID['login_name'];
		$this->formMeta->mode = 'user_update';
		$this->renderAvatar();
		return $this->renderUpdateForm();
	}
	
	public function update(){
		Control::update();
		$this->updateMap();
	}
	
	public function drop(){
		$uid = (int) gg('id');
		if(!empty($uid)){
			db_update('users', array('status' => 'deleted'), $uid);
		}
		execute_set_db();
		document_set_redirect('user');
	}
	
	protected function initJS(){
		head_add_js_var('nameTooShort', tt('Login name is too short.'));
		head_add_js_var('nameNotConformed', tt('Login name is not conformed.'));
		head_add_js_var('nameExists', tt('Login name exists.'));
		head_add_js_var('emailExists', tt('Email address exists.'));
		head_add_js_var('passwdNotChange', tt('Password is empty, hence password is not changed.'));
		head_add_js_var('passwdTooShort', tt('Password is too short.'));
		head_add_js_var('passwdVeryStrong', tt('Password strength is very strong.'));
		head_add_js_var('passwdStrong', tt('Password strength is strong.'));
		head_add_js_var('passwdMedium', tt('Password strength is medium.'));
		head_add_js_var('passwdWeak', tt('Password strength is weak.'));
		head_add_js_var('passwdMismatch', tt('Password is mismathed.'));
		head_add_js('include/external/sha1.js');
	}
	
	protected function renderAvatar(){
		$avatar = $this->dataByID['avatar'];
		if(empty($avatar)) $avatar = 'files/avatar/default.png';
		$image = ROOT_URI.$avatar;
		$this->formMeta->description = '<p align="center"><img src="'.$image.'"></p>';
	}
	
	private function injectGroupForm(){
		$this->groupForm = Model::group(tt('groups'));
		$this->groupForm->isExceptedAdmin = false;
		$this->groupForm->isExceptedGuest = true;
		$this->groupForm->isExceptedUser  = true;
		$this->groupForm->isDB = false;
		$this->modelConnector->addModel('groups', $this->groupForm);
	}
	
	private function getGroupData(){
		$clause = 'WHERE users='.$this->id;
		$this->groupForm->data = db_select_single_column('map', 'groups', $clause, false);
	}
	
	private function updateMap(){
		if(is_array(pp('groups'))){
			$clause = 'users='.((int) $this->id);
			db_drop_many('map', $clause);
			$data = array(
				'users' => $this->id,
				'section' => SECTION,
			);
			foreach(pp('groups') as $key => $value){
				$data['groups'] = $value;
				db_insert('map', $data);
			}
		}
	}
}
?>
