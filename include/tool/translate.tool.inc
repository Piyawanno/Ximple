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

function translate_get($module, $module_id, $language){
	$column = array('id', 'translation');
	$clause = "WHERE modeule='$module' AND module_id='$module_id' AND status=1 AND language='$language'";
	$data = db_select('translation', $column, $clause);
	if(count($data)){
		$translation = unserialize($data[0]['translation']);
		$translation['id'] = $data[0]['translation'];
		return $translation;
	}else{
		return array();
	}
}

function translate_set($translation){
	if(isset($translation['id'])){
	
	}else{
	
	}
}

function translate_add_directory($directory){
	$locale_file = $directory.'/locale/'.LANGUAGE.'.locale.inc';
	if(is_file($locale_file)){
		require_once($locale_file);
	}
}
?>
