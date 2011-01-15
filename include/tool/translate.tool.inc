<?php
function translate_define_language(){
	if(!defined('LANGUAGE')){
		$language = uu('language');
		if($language) define('LANGUAGE', $language);
		else define('LANGUAGE', DEFAULT_LANGUAGE);
	}
	translate_add_directory(ROOT_PATH.'include');
}

function translate_get_language(){
	$language = array(
		'de' => 'Deutsch',
		'th' => 'ไทย',
	);
	return $language;
}

function translate_add_directory($directory){
	$locale_file = $directory.'/locale/'.LANGUAGE.'.locale.inc';
	if(is_file($locale_file)){
		require_once($locale_file);
	}
}
?>
