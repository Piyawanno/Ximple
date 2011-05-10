<?php

global $execute_callable, $execute_mode, $execute_class, $execute_class_extension;

$execute_callable = array();
$execute_class_extension = array();
$execute_class = array();
$execute_mode = 0;

function execute($mode, $params=null, $result=null){
	global $execute_callable;
	$module = execute_get_module($mode);
	execute_include_files($module);
	if(!execute_is_callable($mode)) error_denied();
	if(function_exists($mode) and in_array($mode, $execute_callable)){
		return $mode($params, $result);
	}else{
		return execute_oop($mode, $module, $params, $result);
	}
}

function execute_string($uri, $params=null, $result=null){
	$uri = execute_parse_smart_uri('/'.$uri);
	globalvar_set_get($uri);
	document_lock_set_path();
	$result = execute($uri['mode'], $params, $result);
	globalvar_reset_get();
	document_release_set_path();
	return $result;
}

function execute_oop($mode, $module, $params, $result){
	$class = execute_get_class($mode, $module);
	$success = false;
	$result = '';
	if($class and class_exists($class)){
		$obj = new $class();
		if(!is_a($obj, 'Authority')){
			error_denied();
		}else{
			$method = $obj->getAction($mode);
			$obj->prepareMethod($method);
			if(!$obj->isCallable($method)){
				error_denied();
			}elseif($method){
				$result = $obj->$method();
				$success = true;
			}
		}
	}
	if(!$success) error_not_found();
	return $result;
}

function execute_add_function($mode){
	global $execute_callable;
	if(!in_array($mode, $execute_callable)){
		$execute_callable[] = $mode;
	}
}

function execute_add_class($module, $class){
	global $execute_class;
	include_once(ROOT_PATH.'include/class/Control.class.inc');
	if(!isset($execute_class[$module])){
		$execute_class[$module] = $class;
	}elseif(state_is_develop()){
		$exist_class = $execute_class[$module];
		notify_add_error('Module : '.$module.' has already defined a class : '.$exist_class);
	}
}

function execute_add_extended_class($module, $extension, $class){
	global $execute_class_extension;
	include_once(ROOT_PATH.'include/class/Control.class.inc');
	if(isset($execute_class_extension[$module])){
		if(!isset($execute_class_extension[$module][$extension])){
			$execute_class_extension[$module][$extension] = $class;
		}elseif(state_is_develop()){
			$exist_class = $execute_class[$module];
			notify_add_error('Module : '.$module.' has already defined a class : '.$exist_class);
		}
	}else{
		$execute_class_extension[$module] = array($extension => $class);
	}
	
}

function execute_get_class($mode, $module){
	global $execute_class;
	global $execute_class_extension;
	$splitted =  split('_', $mode);
	if(count($splitted) > 1){
		if(isset($execute_class_extension[$module][$splitted[1]])){
			return $execute_class_extension[$module][$splitted[1]];
		}
	}
	
	if(isset($execute_class[$module])){
		return $execute_class[$module];
	}else{
		return null;
	}
}

function execute_set_site(){
	global $execute_mode;
	$execute_mode = 0;
}


function execute_set_db(){
	global $execute_mode;
	$execute_mode = 1;
}

function execute_set_ajax(){
	global $execute_mode;
	$execute_mode = 2;
}

function execute_set_file(){
	global $execute_mode;
	$execute_mode = 3;
}

function execute_set_print(){
	global $execute_mode;
	$execute_mode = 4;
}

function execute_as_site(){
	global $execute_mode;
	return $execute_mode == 0;
}

function execute_as_db(){
	global $execute_mode;
	return $execute_mode == 1;
}

function execute_as_ajax(){
	global $execute_mode;
	return $execute_mode == 2;
}

function execute_as_file(){
	global $execute_mode;
	return $execute_mode == 3;
}

function execute_as_print(){
	global $execute_mode;
	return $execute_mode == 4;
}

function execute_is_callable($mode){
	global $execute_callable;
	return in_array($mode, $execute_callable) or 1;
}

function execute_get_module($mode){
	$split = split('_', $mode);
	return $split[0];
}

function execute_include_files($module){
	$module_require = cc('module_require');
	if(isset($module_require[$module])){
		$module_require = $module_require[$module];
		translate_add_directory(ROOT_PATH.'module/'.$module.'/');
		if(!is_array($module_require)){
			execute_include(ROOT_PATH.'module/'.$module.'/'.$module_require);
		}else{
			foreach($module_require as $key => $value){
				execute_include(ROOT_PATH.'module/'.$module.'/'.$value);
			}
		}
	}
}

function execute_include($require){
	if(is_file($require)){
		include_once($require);
	}elseif(state_is_develop()){
		error_syslog('Error execute_include_files by module : '.$module.', file : '.$require);
	}else{
		error_not_found();
	}
}

function execute_parse_smart_uri($uri){
	$result = array();
	$splitted = split('\/',$uri);
	$size = count($splitted);
	$result['mode'] = $splitted[1];
	
	if($size >= 3){
		if(ctype_digit($splitted[2])){
			$result['id'] = $splitted[2];
			$begin = 3;
		}else{
			$result['id'] = '0';
			$begin = 2;
		}
		for($i=$begin ; $i <= $size ; $i+=2){
			if(isset($splitted[$i+1])){
				$result[$splitted[$i]] = $splitted[$i+1];
			}
		}
	}
	return $result;
}
?>
