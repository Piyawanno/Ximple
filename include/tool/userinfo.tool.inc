<?php

execute_add_function('userinfo_get_ajax_name');
execute_add_function('userinfo_check_user_exists');
execute_add_function('userinfo_check_email_exists');

function userinfo_get_info($data, $column){
	if(count($data) == 0) return $data;
	$uid = array();
	foreach($data as $key => $value){
		$uid[] = (int)$value[$column];
	}
	$clause = 'WHERE id='.join(' OR id=', $uid);
	$user_info = db_select('users', array('id', 'login_name', 'email', 'avatar', 'space_used'), $clause);
	foreach($data as $key => $value){
		$id = $value[$column];
		if(isset($user_info[$id])){
			if(empty($user_info[$id]['avatar'])){
				$user_info[$id]['avatar'] = 'files/avatar/default.png';
			}
			$user_config = io_unserialize(ROOT_PATH.'files/account/'.$id);
			$user_info[$id]['config'] = $user_config;
			$data[$key][$column] = $user_info[$id];
		}
	}
	return $data;
}

function userinfo_get_info_by_id($uid){
	$dummy = array($uid => array('id' => $uid));
	$info = userinfo_get_info($dummy, 'id');
	return $info[$uid]['id'];
}

function userinfo_name_to_id($name){
	if(count($name)){
		$clause = "WHERE login_name='".join("' OR login_name='", $name)."'";
		return db_select_single_column('users', 'id', $clause);
	}else{
		return array();
	}
}

function userinfo_group_to_id($group_id){
	if(count($group_id)){
		$clause = "WHERE (groups=".join(' OR groups=', $group_id).') AND section='.SECTION.' GROUP BY users';
		return db_select_single_column('map', 'users', $clause, false);
	}else{
		return array();
	}
}

function userinfo_get_used_space($uid){
	$space = db_select('users', array('space_used'), "WHERE id='".(int)$uid."'");
	if(count($space))return $space[0]['space_used'];
	else return null;
}

function userinfo_decrease_used_space($uid, $space){
	// More query is better than concept changing
	// Ximple is not designed for such query : "UPDATE users SET space_used=space_used-$space".
	$space = userinfo_get_used_space($uid) - $space;
	db_update('users', array('space_used' => $space), $uid);
}

function userinfo_increase_used_space($uid, $space){
	$space = userinfo_get_used_space($uid) + $space;
	db_update('users', array('space_used' => $space), $uid);
}

function userinfo_get_ajax_name(){
	if(!authority_is_guest()){
		$wildcard = addslashes((string) gg('wildcard'));
		if(strlen($wildcard)){
			$clause = "WHERE login_name LIKE '".$wildcard."%' and section=".SECTION;
			$user_name = db_select_single_column('users', 'login_name', $clause);
			execute_set_ajax();
			return '<option>'.join('</option><option>', $user_name).'</option>';
		}
	}
}

function userinfo_check_user_exists(){
	$uid = gg('uid');
	if(empty($uid)){
		$clause = "WHERE login_name='".addslashes((string) gg('login_name'))."'";
	}else{
		$clause = "WHERE login_name='".addslashes((string) gg('login_name'))."' AND id!=".((int)$uid);
	}
	$user_name = db_select_single_column('users', 'login_name', $clause);
	execute_set_ajax();
	if(count($user_name)){
		return 'exist';
	}else{
		return 'not exist';
	}
}

function userinfo_check_email_exists(){
	$uid = gg('uid');
	if(empty($uid)){
		$clause = "WHERE email='".addslashes((string) gg('email'))."'";
	}else{
		$clause = "WHERE email='".addslashes((string) gg('email'))."' AND id!=".((int)$uid);
	}
	$email = db_select_single_column('users', 'email', $clause);
	execute_set_ajax();
	if(count($email)){
		return 'exist';
	}else{
		return 'not exist';
	}
}

?>
