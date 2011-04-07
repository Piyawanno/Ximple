<?php
authority_owner('user_admin', account_get_uid());
execute_add_function('account');
execute_add_function('account_save');

include_once(ROOT_PATH.'module/user/User.class.inc');

function account(){
	include_once(ROOT_PATH.'include/class/QuickFormRender.class.inc');
	$form = array(account_render_form());
	$user = new User();
	$user->id = account_get_uid();
	$user->selectByID($user->column);
	document_set_path(tt('Configure Account'));
	return $user->account(account_render_additional($form));
}

function account_save(){
	$user = new User();
	$user->prepareModifyDB();
	$user->update();
	$account_dir = ROOT_PATH.'files/account/';
	if(!is_dir($account_dir)) mkdir($account_dir);
	$config = pp();
	$config['signature'] = strip_tags($config['signature']);
	io_serialize($config, $account_dir.USER_ID);
	document_set_redirect('account');
	notify_add_info(tt('Your account configuration has been successfully updated.'));
}

function account_get_uid(){
	$mode_id = mid();
	if($mode_id != 0) return $mode_id;
	else return USER_ID;
}

function account_render_form(){
	$form_render = new QuickFormRender('user');
	$permission_select = array(
		0 => tt('Everybody included anonymous visitor'),
		1 => tt('All authenticated users'),
		2 => tt('Only you and administration'),
	);
	
	$editor_select = array(
		0 => tt('TinyMCE WYSIWYG editor without code-writer'),
		1 => tt('TinyMCE WYSIWYG editor with code-writer'),
		2 => tt('Normal text editor with markdown syntax'),
	);
	
	$signature = Model::char(tt('signature'));
	$signature->data = uu('signature');
	$language = Model::select(tt('default language for my user interface'), translate_get_interface_language());
	$language->data = uu('language');
	$profile = Model::radio(tt('who can see my profile'), $permission_select);
	$profile->data = uu('profile_permission');
	$email = Model::radio(tt('who can send me an email'), $permission_select);
	$email->data = uu('email_permission');
	
	$form_render->append('signature', $signature);
	$form_render->append('language', $language);
	$form_render->append('profile_permission', $profile);
	$form_render->append('email_permission', $email);
	return $form_render->render();
}

function account_render_additional($form){
	$additional = cc('account_config');
	if(is_array($additional)){
		foreach($additional as $key => $value){
			$form[] = execute_string($value);
		}
	}
	return $form;
}

?>
