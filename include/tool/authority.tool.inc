<?php
/// @file
/// This file provides functions for authority checking.
///
/// @author bow_der_kleine <bow_der_kleine@yahoo.de>

/// Authorization function of X-BLC.
/// It should be minimal and fast.
/// @param $users  : array of user id, which should get permission.
/// @param $groups : array of group id, which should get permission.
function authority($users=array(), $groups=array(), $first_check=false){
	authority_handle_login();
	authority_init_salt();
	$crypt = authority_get_crypt();
	if($crypt != ss('authority') or authority_is_login()){
		$user_db = authority_get_user_array();
		authority_define_user_passwd($user_db);
		$_SESSION['authority'] = $crypt;
		if(USER_PASSWD == ss('login_password') and isset($user_db[0])){
			authority_handle_user($user_db[0]['id']);
		}else{
			authority_handle_guest();
			authority_define_const();
			return false;
		}
	}
	authority_define_const();
	return authority_check_users_groups($users, $groups);
}

/// Set $_SESSION and redirect by loggin-in and logging-out.
/// login_name_hash is applied to avoid SQL injection.
function authority_handle_login(){
	if(authority_is_login()){
		$_SESSION['login_name'] = addslashes((string)pp('login_name'));
		$_SESSION['login_name_hash'] = sha1(pp('login_name'));
		$_SESSION['login_password'] = pp('login_password');
		$_SESSION['login_salt'] = pp('login_salt');
		execute_set_db();
		document_set_redirect(pp('redirect'));
	}elseif(authority_is_logout()){
		authority_clear_session();
		execute_set_db();
	}
}

/// Check user authority by group name.
function authority_group($gid){
	return authority(array(), cc($gid));
}

/// Check user authority by User-ID.
function authority_user($uid){
	if(empty($uid)) return false;
	return authority(array($uid), array());
}

/// Check user authority by group name and User-ID (most used for checking data owner).
function authority_owner($gid, $uid){
	return authority(array($uid), cc($gid));
}

/// Get cryptographic for session authorization.
/// @return Cryptographic for session authorization.
function authority_get_crypt(){
	return sha1(session_id().cc('antispam_salt'));
}

/// Is user a guest (who did not log in).
/// @return TRUE, if user is a guest.
function authority_is_guest(){
	if(ss('ximple_id') != -1 and USER_PASSWD == ss('login_password')) return false;
	else return true;
}

/// Is user a admin (who can do everything in section).
/// @return TRUE, if user is a admin.
function authority_is_admin(){
	return in_array(1, ss('login_group'));
}

/// Check state of user in in given array of users of groups
/// @param $users  : array of user id, which should get permission.
/// @param $groups : array of group id, which should get permission.
/// @return TRUE, if user is in given array of users of groups.
function authority_check_users_groups($users, $groups){
	if(is_array($groups) and in_array(2, $groups)) return true;
	$groups = array();
	foreach($users as $key => $user){
		if($user == -1) unset($users[$key]);
	}
	$intersect_groups = array_intersect(ss('login_group'), $groups);
	$in_groups = count($intersect_groups);
	$in_users  = in_array(USER_ID, $users);
	return $in_groups or $in_users or in_array(1, ss('login_group'));
}

/// Initialize session salt.
function authority_init_salt(){
	if(ss('login_salt') == null){
		$_SESSION['login_salt'] = '';
	}
}

/// Get user array from database for authorization.
/// @return Array of logging-in user information from data base.
function authority_get_user_array(){
	if(strlen(ss('login_name'))){
		$clause = "WHERE (login_name='".ss('login_name')."') LIMIT 1";
		$user_db = db_select('users', array('id', 'password'), $clause);
		if(count($user_db) == 0){
			$clause = "WHERE (email='".ss('login_name')."') ORDER BY id LIMIT 1";
			$user_db = db_select('users', array('id', 'password'), $clause);
		}
	}else{
		$user_db = array();
	}
	return array_values($user_db);
}

/// Define constant USER_PASSWD.
function authority_define_user_passwd($user_db){
	if(count($user_db)){
		$sha = $user_db[0]['password'].ss('login_salt');
		if(!defined('USER_PASSWD')){
			define('USER_PASSWD', sha1($user_db[0]['password'].ss('login_salt')));
		}
	}elseif(!defined('USER_PASSWD')){
		define('USER_PASSWD', '');
	}
}

/// Handle guest user or person, who did not login.
function authority_handle_guest(){
	$_SESSION['login_name'] = "guest";
	$_SESSION['ximple_id'] = -1;
	$_SESSION['login_group'] = array(2);
	if(authority_is_login()){
		sleep(3);
		include('head.tool.inc');
		$message = tt('Sorry !!! wrong name or password. Please try again.');
		io_write_log($message, 'fail_login');
		error_syslog($message);
	}
}

/// Handle regular user or person, who has already logged-in.
/// @param $uid : ID of the user.
function authority_handle_user($uid){
	$map = db_select_single_column('map', 'groups', "WHERE users='".(int)$uid."' AND section=".SECTION, false);
	$_SESSION['login_group'] = $map;
	$_SESSION['ximple_id'] = $uid;
}

/// Define constant for user.
function authority_define_const(){
	if(!defined('USER_ID')){
		define('USER_ID', ss('ximple_id'));
	}
	if(!defined('USER_NAME')){
		define('USER_NAME', ss('login_name'));
	}
	if(!defined('USER_PASSWD')){
		define('USER_PASSWD', ss('login_password'));
	}
}

function authority_is_login(){
	return pp('login') == 'login';
}

function authority_is_logout(){
	return pp('logout') != null;
}


/// Clear session and domain cookie.
function authority_clear_session(){
	if (ini_get("session.use_cookies")) {
		$params = session_get_cookie_params();
		setcookie(session_name(), '', time() - 42000,
			$params["path"], $params["domain"],
			$params["secure"], $params["httponly"]
		);
	}
}
?>
