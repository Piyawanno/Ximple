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

function translate_get_published($module, $module_id, $language){
	$clause = "WHERE module='$module' AND module_id='$module_id' AND status=1 AND language='$language'";
	return translate_get($clause);
}

function translate_get_all($module, $module_id, $language){
	$clause = "WHERE module='$module' AND module_id='$module_id' AND language='$language'";
	return translate_get($clause);
}

function translate_get($clause){
	$column = array('id', 'translation');
	$data = db_select('translation', $column, $clause);
	if(count($data)){
		$data = array_values($data);
		$translation = unserialize($data[0]['translation']);
		$translation['id'] = $data[0]['translation'];
		return $translation;
	}else{
		return array();
	}
}

function translate_set($translation){
	$data = array(
		'status' => $translation['status'],
		'module' => $translation['module'],
		'module_id' => $translation['module_id'],
		'language' => $translation['language'],
		'translation' => serialize($translation),
	);
	if(isset($translation['id'])){
		db_update('translation', $data, $translation['id']);
	}else{
		db_insert('translation', $data);
	}
}

function translate_add_directory($directory){
	$locale_file = $directory.'/locale/'.LANGUAGE.'.locale.inc';
	if(is_file($locale_file)){
		require_once($locale_file);
	}
}
?>
