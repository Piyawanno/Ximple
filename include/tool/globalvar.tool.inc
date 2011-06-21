<?php
/// @file
/// This file provides functions for global variables access.
/// The global variables should be read only to minimize error pron.
/// The followed functions are exceptions
///
/// @author Kittipong Piyawanno <k.piyawanno@gmail.com>

/// Internal global variables for globalvar-tool.
/// These variables should not be used outside this file.
global $global_get, $global_post;

$global_get  = $_GET;
$global_post = $_POST;
$global_config_translated = false;

/// Access $_POST variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $_POST[$key]
function pp($key=null){
	global $global_post;
	if($key == null) return $global_post;
	elseif(isset($global_post[$key])) return $global_post[$key];
	else return null;
}

/// Access $_GET variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $_GET[$key]
function gg($key=null){
	global $global_get;
	if($key == null) return $global_get;
	elseif(isset($global_get[$key])) return $global_get[$key];
	else return null;
}

/// Access $_SESSION variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $_SESSION[$key]
function ss($key=null){
	if($key == null) return $_SESSION;
	elseif(isset($_SESSION[$key])) return $_SESSION[$key];
	else return null;
}

/// Access $$_FILES variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $$_FILES[$key]
function ff($key=null){
	if($key == null) return $_FILES;
	elseif(isset($_FILES[$key])) return $_FILES[$key];
	else return null;
}

/// Access $GLOBALS variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $GLOBALS[$key]
function ww($key=null){
	if($key == null) return $GLOBALS;
	elseif(isset($GLOBALS[$key])) return $GLOBALS[$key];
	else return null;
}

/// Access $_SERVER variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $_SERVER[$key]
function vv($key=null){
	if($key == null) return $_SERVER;
	elseif(isset($_SERVER[$key])) return $_SERVER[$key];
	else return null;
}

function cc($key=null){
	$config = $GLOBALS['config'];
	$config['increase_read'] = array();
	$config['interp_info'] = '1';
	$config['language'] = 'th';
	$config['dash_icons'] = array();
	if($key == null) return $config;
	elseif(isset($GLOBALS['tmp_config'][$key])) return $GLOBALS['tmp_config'][$key];
	elseif(isset($config[$key])) return $config[$key];
	else return null;
}

function ucc($key=null){
	$config = $GLOBALS['untranslated_config'];
	$config['increase_read'] = array();
	$config['interp_info'] = '1';
	$config['language'] = 'th';
	$config['dash_icons'] = array();
	if($key == null) return $config;
	elseif(isset($GLOBALS['tmp_config'][$key])) return $GLOBALS['tmp_config'][$key];
	elseif(isset($config[$key])) return $config[$key];
	else return null;
}

function uu($key=null){
	if(!isset($GLOBALS['account'])){
		$account_dir = FILES_PATH.'account/';
		if(!is_dir($account_dir)) mkdir($account_dir);
		$GLOBALS['account'] = io_unserialize($account_dir.USER_ID);
	}
	if(!$GLOBALS['account']){
		$GLOBALS['account'] = array(
			'profile_permission' => 1,
			'email_permission' => 0,
			'editor' => 0,
		);
	}
	if($key == null) return $GLOBALS['account'];
	elseif(isset($GLOBALS['account'][$key])) return $GLOBALS['account'][$key];
	else return null;
}

global $locale;
$locale = array();
function tt($key){
	global $locale;
	if(isset($locale[$key]) and strlen($locale[$key])) return $locale[$key];
	else return $key;
}

function mm(){
	return gg('mode');
}

function mid(){
	return gg('id');
}

function pid(){
	return gg('page');
}

function globalvar_set_get($get){
	global $global_get;
	$global_get = $get;
}

function globalvar_reset_get(){
	global $global_get;
	$global_get = $_GET;
}

function globalvar_set_post($post){
	global $global_post;
	$global_post = $post;
}

function globalvar_reset_post(){
	global $global_post;
	$global_post = $_POST;
}

function globalvar_add_locale($additional){
	global $locale;
	$locale = array_merge($locale, $additional);
}
?>
