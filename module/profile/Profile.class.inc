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
		
		$this->addAction('profile_write_mail', 'writeMail');
		$this->addAction('profile_send_mail', 'sendMail');
		
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'writeMail');
		$this->addAccessMethod('guest', 'sendMail');
		$this->init(new ProfileModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		$uid = $this->getUID();
		$this->select($this->column, 'WHERE owner='.$uid);
		$user_info = userinfo_get_info_by_id($uid);
		head_add_css('profile.css');
		$data = array();
		foreach($this->data as $key => $value){
			$data[$value['profiletype']][] = $value['profile'];
		}
		$editable = authority_owner('profile_admin', $uid);
		$renderArray = array(
			'user' => $user_info,
			'data' => $data,
			'uid' => $uid,
			'allow_email' => $this->getAllowEmail($editable),
			'readable' => $this->getReadable($editable),
			'editable' => $editable,
		);
		return render($renderArray, 'profile.tpl', 'profile');
	}
	
	public function writeMail(){
		$uid = $this->getUID();
		require_once('ProfileMailForm.class.inc');
		document_set_path(sprintf(tt('Send email to %s'), gg('send_to')));
		$form = new ProfileMailForm($this->id, $this->dataByID['name'], $this->dataByID['enable_attachment']);
		return $form->render($this->dataByID['description']);
	}
	
	public function sendMail(){
		execute_set_db();
		document_set_redirect('profile/'.gg('id'));
		if(pp('email')){
			$sender = pp('email');
		}else{
			$userInfo = userinfo_get_info_by_id(pp('sender'));
			$sender = $userInfo['email'];
		}
		$message = sprintf('<p>'.tt('Email from %s').'</p>', $sender).pp('message');
		$userInfo = userinfo_get_info_by_id(pp('receiver'));
		$receiver = $userInfo['email'];
		$result = mail_send($receiver, pp('subject'), $message, true, $this->attachment);
		if($result !== true){
			notify_add_error($result);
		}
	}
	
	private function getReadable($editable){
		$permission = (int) uu('profile_permission');
		$readable = ($permission == 0);
		$readable = ($readable or ($permission == 1 and !authority_is_guest()));
		$readable = ($readable or $editable);
		return $readable;
	}
	
	private function getAllowEmail($editable){
		$permission = (int) uu('email_permission');
		$allow_email = ($permission == 0);
		$allow_email = ($allow_email or ($permission == 1 and !authority_is_guest()));
		$allow_email = ($allow_email or $editable);
		return $allow_email;
	}
	
	private function getUID(){
		$uid = MODE_ID;
		if(empty($uid)) $uid = USER_ID;
		if($uid <= 0) error_denied(); 
		return $uid;
	}
}
?>
