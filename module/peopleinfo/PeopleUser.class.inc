<?php
execute_add_extended_class('peopleinfo', 'user', 'PeopleUser');
include_once(MODULE_PATH.'user/User.class.inc');
include_once('peopleinfo.tool.inc');

class PeopleUser extends User{
	function PeopleUser(){
		$this->addAction('peopleinfo_user_save', 'insert');
		$this->addAction('peopleinfo_user_get', 'getUserOption');
		
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'user';
		$this->tableName = 'users';
		$this->setAdmin('user_admin');
		
		$this->insertNotify = sprintf(tt('%s has been successfully inserted.'), tt('User'));
		$this->updateNotify = sprintf(tt('%s has been successfully updated.'), tt('User'));
		$this->dropNotify = sprintf(tt('%s has been successfully dropped.'), tt('User'));
		
		$this->init(new UserModel());
	}
	
	public function write(){
		execute_set_ajax();
		$this->initJS();
		head_add_js_var('insertUser', true);
		$this->moduleTitle = tt('Add User to People Information Center');
		$this->formMeta->id = 'user';
		$this->formMeta->title = $this->moduleTitle;
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'submitPeopleUserForm';
		$this->formMeta->mode = 'peopleinfo_user_save';
		return $this->renderInsertForm();
	}
	
	public function insert(){
		User::insert();
		$groups = cc('peopleinfo_related');
		if(count($groups)){
			foreach($groups as $key => $value){
				$clause = 'users='.((int) $this->id).' AND groups='.$value;
				db_drop_many('map', $clause);
				$data = array(
					'users' => $this->id,
					'groups' => $value,
					'section' => SECTION,
				);
				db_insert('map', $data);
			}
		}
	}
	
	public function getUserOption(){
		execute_set_ajax();
		$people = peopleinfo_get_unprocessed_user();
		$render = '';
		foreach($people as $key => $value){
			$render .= '<option value="'.$key.'">'.$value.'</option>';
		}
		return $render;
	}
}
?>
