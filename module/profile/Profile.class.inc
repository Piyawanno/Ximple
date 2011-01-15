<?php
execute_add_class('profile', 'Profile');
include('ProfileModel.class.inc');

class Profile extends Control{
	function Profile(){
		$this->tableName = 'profile';
		$this->moduleName = 'profile';
		$this->moduleTitle = tt('User-Profile');
		$this->ownerColumn = 'owner';
		$this->setAdmin('profile_admin');
		$this->addAccessMethod('guest', 'index');
		$this->init(new ProfileModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	function index(){
		$uid = MODE_ID;
		if(empty($uid)) $uid = USER_ID;
		$this->select($this->column, 'WHERE owner='.$uid);
		$user_info = userinfo_get_info_by_id($uid);
		head_add_css('profile.css');
		$data = array();
		foreach($this->data as $key => $value){
			$data[$value['profiletype']][] = $value['profile'];
		}
		$editable = authority_owner('profile_admin', $uid);
		$permission = (int) uu('profile_permission');
		$readable = ($permission == 0);
		$readable = ($readable or ($permission == 1 and !authority_is_guest()));
		$readable = ($readable or $editable);
		$renderArray = array(
			'user' => $user_info,
			'data' => $data,
			'uid' => $uid,
			'readable' => $readable,
			'editable' => $editable,
		);
		return render($renderArray, 'profile.tpl', 'profile');
	}
}
?>
