<?php
execute_add_function('translate_set_language');

function translate_define_language(){
	if(!defined('LANGUAGE')){
		$language = uu('language');
		if($language) define('LANGUAGE', $language);
		else define('LANGUAGE', DEFAULT_LANGUAGE);
	}
	translate_add_directory(ROOT_PATH.'include');
}

function translate_get_interface_language(){
	$language = array(
		'en' => 'English',
		'de' => 'Deutsch',
		'th' => 'ไทย',
	);
	return $language;
}

function translate_get_language(){
	$language = ss('language');
	if(strlen($language) == 0){
		$language = cc('supported_language');
		if(is_array($language) and count($language)){	
			$language = array_keys($language);
			$language = $language[0];
		}else{
			$language = 'DEFAULT';
		}
	}
	return $language;
}

function translate_set_language(){
	$_SESSION['language'] = gg('language');
	$language = cc('supported_language');
	$language = $language[gg('language')];
	$message  = sprintf(tt('Contents are set to %s language. '), $language);
	$message .= tt('Only translated contents will be shown. ');
	$message .= tt('Other cases, the original content will be shown.');
	notify_add_info($message);
	execute_set_db();
	document_set_redirect_back();
}

function translate_content($content, $module, $module_id){
	$langauge = translate_get_language();
	if(strlen($langauge)){
		$translated = translate_get_published_data($module, $module_id, $langauge);
		if(isset($translated['id'])){
			unset($translated['id']);
			unset($translated['status']);
			$result = array();
			foreach($content as $key => $value){
				if(isset($translated[$key])) $result[$key] = $translated[$key];
				else $result[$key] = $value;
			}
			return $result;
		}else{
			return $content;
		}
	}else{
		return $content;
	}
}

function translate_get_published_data($module, $module_id, $langauge){
	$clause = "WHERE module='$module' AND module_id='$module_id' AND status=1 AND language='$langauge'";
	return translate_get_data($clause);
}

function translate_get_all_data($module, $module_id, $language){
	$clause = "WHERE module='$module' AND module_id='$module_id' AND language='$language'";
	return translate_get_data($clause);
}

function translate_get_data($clause){
	$column = array('id', 'translation', 'status');
	$data = db_select('translation', $column, $clause);
	if(count($data)){
		$data = array_values($data);
		$translation = unserialize($data[0]['translation']);
		$translation['id'] = $data[0]['id'];
		$translation['status'] = $data[0]['status'];
		return $translation;
	}else{
		return array('status' => 0);
	}
}

function translate_set_data($translation){
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
