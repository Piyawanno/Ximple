<?php
function evaluation_get_model($model_reference=null){
	$model_directory = ROOT_PATH.'module/evaluation/model/';
	$model_array = io_get_directory_entry($model_directory);
	$model = array();
	foreach($model_array as $key => $value){
		require_once($model_directory.$value);
		$model_name = str_replace('.model.inc', '', $value);
		if(function_exists($model_name)){
			$model[$model_name] = $model_name();
		}
	}
	if(!isset($model[$model_reference])) return $model;
	else $model[$model_reference];
}

function evaluation_get_model_name(){
	$model = evaluation_get_model();
	$model_name = array();
	foreach($model as $key => $value){
		$model_name[$key] = $value['name'];
	}
	return $model_name;
}

function evaluation_check_model_exists($model){
	$model_array = evaluation_get_model();
	return in_array($model, array_keys($model_array));
}

function evaluation_get_reference($model_name){
	$model_array = evaluation_get_model();
	$model = $model_array[$model_name]['model'];
	$reference = array();
	foreach($model as $name => $sub_model){
		foreach($sub_model as $key => $value){
			$reference[] = $key;
		}
	}
	return $reference;
}
?>
