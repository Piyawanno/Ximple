<?php

execute_add_function('notify_check');
execute_add_function('notify_mark_as_read');

global $notify, $notify_savable;
$notify_savable = true;

$notify = array();

function notify_add_info($message, $uid=USER_ID){
	notify_add($message, 'info', $uid);
}

function notify_add_tip($message, $uid=USER_ID){
	notify_add($message, 'tip', $uid);
}

function notify_add_warning($message, $uid=USER_ID){
	notify_add($message, 'warning', $uid);
	io_write_log($message, 'notify_warning');
}

function notify_add_error($message, $uid=USER_ID){
	notify_add($message, 'error', $uid);
	io_write_log($message, 'notify_error');
}

function notify_add($message, $mode, $uid){
	global $notify;
	if(!isset($notify[$uid]['number']) or $notify[$uid]['number'] == 0){
		$notify[$uid] = array(
			'number' => 0,
			'info' => '',
			'tip' => '',
			'warning' => '',
			'error' => '',
		);
	}
	$notify[$uid]['number']++;
	$notify[$uid][$mode] .= '<li>'.$message.'</li>';
}

function notify_save(){
	global $notify, $notify_savable;
	if($notify_savable){
		foreach($notify as $uid => $entry){
			$file_name = notify_get_file_name($uid);
			$entry = notify_merger($entry, $file_name);
			io_serialize($entry, $file_name);
		}
	}
}

function notify_merger($entry, $file_name){
	if(is_file($file_name.'.php')){
		$old_entry = io_unserialize($file_name);
		foreach($entry as $key => $value){
			if($key == 'number') $entry[$key] += $old_entry[$key];
			else $entry[$key] = $old_entry[$key].$value;
		}
	}
	return $entry;
}

function notify_render(){
	$file_name = notify_get_file_name(USER_ID);
	$read_notify = io_unserialize($file_name);
	if($read_notify['number']){
		unlink($file_name.'.php');
		return notify_render_item($read_notify);
	}
}

function notify_render_item($notify, $show_close=true){
	$render_array = array(
		'show_close' => $show_close,
		'data' => $notify,
		'title' => array(
			'info' => tt('Information Notification'),
			'tip' => tt('Tip Notification'),
			'warning' => tt('Warning Notification'),
			'error' => tt('Error Notification'),
		),
	);
	return render($render_array, 'notify.tpl', 'notify');
}

function notify_get_file_name($uid){
	if($uid == -1){
		$file_name = session_id();
	}else{
		$file_name = (string) $uid;
	}
	$dir_name = FILES_PATH.'notify/';
	if(!is_dir($dir_name)) mkdir($dir_name);
	return $dir_name.$file_name;
}

function notify_check(){
	global $notify_savable;
	execute_set_ajax();
	$file_name = notify_get_file_name(USER_ID);
	$read_notify = io_unserialize($file_name);
	if($read_notify['number']){
		$render = notify_render_item($read_notify, false);
		$rener_array = array(
			'number' => $read_notify['number'],
			'notify' => $render,
		);
		$notify_savable = false;
		return render($rener_array, 'notify_check.tpl', 'notify_check');
	}
}

function notify_mark_as_read(){
	global $notify_savable;
	$file_name = notify_get_file_name(USER_ID);
	unlink($file_name.'.php');
	$notify_savable = true;
}


function notify_subscribe($message, $uid, $reference){
	$subscribe_array = user_info_get_config($uid, 'subscribe');
	if(!is_array($subscribe_array)){
		$subscribe_array = array();
	}
	
	if(in_array($reference, $subscribe_array)){
		require_once('mail.tool.inc');
		$user_info = userinfo_get_info_by_id($uid);
		$subject = notify_get_subscribe_subject();
		mail_send($user_info['email'], $subject, $message, true);
	}
}

function notify_multiple_subscribe($message, $uid, $reference){
	$subcribable_uid = array();
	foreach($uid as $key => $value){
		$subscribe_array = user_info_get_config($value, 'subscribe');
		if(!is_array($subscribe_array)){
			$subscribe_array = array();
		}
		if(in_array($reference, $subscribe_array)){
			$subcribable_uid[] = $value;
		}
	}
	
	if(count($subcribable_uid)){
		require_once('mail.tool.inc');
		$email = join(',', userinfo_get_email($subcribable_uid));
		$subject = notify_get_subscribe_subject();
		mail_send($email, $subject, $message, true);
	}
}

function notify_subscribe_by_mode($message, $mode){
	$uid = io_unserialize(FILES_PATH.'subscribe/'.$mode);
	if(is_array($uid)){
		require_once('mail.tool.inc');
		$email = join(',', userinfo_get_email($subcribable_uid));
		$subject = notify_get_subscribe_subject();
		mail_send($email, $subject, $message, true);
	}
}

function notify_get_subscribe_subject(){
	return '['.cc('section_name').'] '.tt('Notification (not reply)');
}

function notify_direct_subscribe($message, $email){
	require_once('mail.tool.inc');
	$subject = notify_get_subscribe_subject();
	mail_send($email, $subject, $message, true);
}

function notify_add_subscribe($module, $label){
	$subscribe = cc('subscribable_module');
	$subscribe[$module] = $label;
	config_set('subscribable_module', $subscribe);
}

function notify_drop_subscribe($module){
	$subscribe = cc('subscribable_module');
	unset($subscribe[$module]);
	config_set('subscribable_module', $subscribe);
}
?>
