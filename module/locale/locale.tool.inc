<?php
function locale_get($directory, $language){
	if(strlen($directory)){
		$locale = array();
		$file = locale_get_file(ROOT_PATH.$directory, array());
		$key = locale_get_key($file);
		locale_add_predefined($language);
		$key = locale_check_exist($key);
		return locale_render_code($directory, $language, $key);
	}
}

function locale_render_code($directory, $language, $key){
	if(count($key)){
		$locale = locale_get_processed($directory, $language, $key);
		return "&lt;?php\nglobalvar_add_locale(".input_dump_var($locale).");\n?&gt;";
	}
}

function locale_get_file($directory, $file){
	if(is_dir($directory)){
		$entry = io_get_directory_entry($directory);
		foreach($entry as $key => $value){
			$path = $directory.'/'.$value;
			if(is_dir($path)) $file = locale_get_file($path, $file);
			else $file[] = $path;
		}
	}
	return $file;
}

function locale_get_key($file){
	$key = array();
	foreach($file as $value){
		$code = io_read_file($value);
		$key  = array_merge($key, locale_regular_expression($code));
	}
	return array_unique($key);
}

function locale_regular_expression($code){
	$key = array();
	$code = str_replace('\"', '{backslash_double}', $code);
	$code = str_replace("\\'", '{backslash_single}', $code);
	preg_match_all("/[\W](tt)[\s]*\([\s]*\'[^\']*\'[\s]*\)/", $code, $out);
	foreach($out[0] as $tt){
		$tt = substr($tt, 3);
		$tt = preg_replace("/[\s]*\([\s]*\'/", "", $tt);
		$tt = preg_replace("/\'[\s]*\)/", "", $tt);
		$tt = str_replace('{backslash_single}', "\\'", $tt);
		$key[] = $tt;
	}

	preg_match_all('/[\W](tt)[\s]*\([\s]*\"[^\"]*\"[\s]*\)/', $code, $out);
	foreach($out[0] as $tt){
		$tt = substr($tt, 3);
		$tt = preg_replace('/[\s]*\([\s]*\"/', "", $tt);
		$tt = preg_replace('/\"[\s]*\)/', "", $tt);
		$tt = str_replace('{backslash_double}', "\\\"", $tt);
		$key[] = $tt;
	}
	return $key;
}

function locale_add_predefined($language){
	$predefined = array(
		INCLUDE_PATH,
		MODULE_PATH.'content',
	);
	foreach($predefined as $key => $value){
		$file = $value.'locale/'.$language.'.locale.inc';
		if(is_file($file)) require_once($file);
	}
}

function locale_check_exist($key){
	global $locale;
	return array_diff($key, array_keys($locale));
}

function locale_get_processed($directory, $language, $key){
	global $locale;
	$processed = array();
	$file = $directory.'/locale/'.$language.'.locale.inc';
	if(is_file($file)) require_once($file);
	foreach($key as $tt){
		if(isset($locale[$tt])) $processed[$tt] = $locale[$tt];
		else $processed[$tt] = '';
	}
	return $processed;
}

function locale_init(){
	$modules = io_get_directory_entry(MODULE_PATH);
	foreach($modules as $module){
		locale_init_module($module);
	}
}

function locale_get_module(){
	$module = io_get_directory_entry(MODULE_PATH);
	return array_combine($module, $module);
}

function locale_init_module($module){
	$languages = translate_get_interface_language();
	$locale_directory = MODULE_PATH.$module.'/locale/';
	if(!is_dir($locale_directory)) mkdir($locale_directory);
	foreach($languages as $language => $label){
		$code = locale_get('module/'.$module, $language);
		$code = str_replace('&lt;', '<', $code);
		$code = str_replace('&gt;', '>', $code);
		if(strlen($code)){
			$file = $locale_directory.$language.'.locale.inc';
			io_write_file($file, $code);
		}
	}
}
?>
