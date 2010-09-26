<?php
/// @file
/// This file provides functions for global variables access.
/// The global variables should be read only to minimize error pron.
/// The followed functions are exceptions
///
/// @author bow_der_kleine <bow_der_kleine@yahoo.de>
/// @state complete


/// Access $_POST variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $_POST[$key]
function pp($key=null){
	if($key == null) return $_POST;
	elseif(isset($_POST[$key])) return $_POST[$key];
	else return null;
}

/// Access $_GET variable.
/// @param $key : key to access by default (null) the whole array is returned.
/// @return $_GET[$key]
function gg($key=null){
	if($key == null) return $_GET;
	elseif(isset($_GET[$key])) return $_GET[$key];
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
	$config['foot_text'] = '<p>ข้อเขียนในเว็บนี้ เฉพาะทีเจ้าของเว็บเป็นผู้เขียนเอง เอาไปใช้ได้โดยไม่ต้องขออนุญาต แต่ต้องแสดงที่มา และต้องไม่ใช่เพื่อการแสวงหาประโยชน์ในทางธุรกิจ  <br /> <br /> Copyleft Created by bow_der_kleine pround to use <a href="http://www.combiolaw.de/xblc">X-BLC</a></p>';
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
		$account_dir = ROOT_PATH.'files/account/';
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

$locale = array();
function tt($key){
	global $locale;
	if(isset($locale[$key]) and strlen($locale[$key])) return $locale[$key];
	else return $key;
}

?>
