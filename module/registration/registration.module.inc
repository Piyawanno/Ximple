<?php
registration_switch_load();

function registration_switch_load(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('RegistrationConfig.class.inc');
	}else{
		execute_add_function('registration');
		execute_add_function('registration_save');
		execute_add_function('registration_confirm');
		document_set_path(tt('Registration', 'registration'));
		include('registration.tool.inc');
	}
}

function registration(){
	if(cc('registration_enable')){
		include(ROOT_PATH.'include/class/Control.class.inc');
		include(ROOT_PATH.'module/user/User.class.inc');
		$user = new User();
		return $user->registration();
	}else{
		registration_off();
	}
}

function registration_save($reply_mode){
	if(cc('registration_enable')){
		if(strlen($reply_mode) == 0) $reply_mode = 'registration_confirm';
		registration_save_user($reply_mode);
	}else{
		registration_off();
	}
}

function registration_confirm(){
	$register_dir = ROOT_PATH.'files/registration/';
	$user = io_unserialize($register_dir.gg('key1'));
	if(is_array($user) and $user['key'] == gg('key2')){
		$user['login_name_hash'] = sha1($user['login_name']);
		unset($user['key']);
		$uid = db_insert('users', $user);
		$p = tt('Congratulation and welcome to %s. Your registration is completed.');
		notify_add_info(sprintf($p, cc('section_name')));
		unlink($register_dir.gg('key1').'.php');
		execute_set_db();
		document_set_redirect('');
		return $uid;
	}else{
		registration_error();
		execute_set_db();
		document_set_redirect('');
	}
}

?>
