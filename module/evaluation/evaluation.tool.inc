<?php
function evaluation_get_model(){
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
	return $model;
}

function evaluation_get_model_name(){
	$model = evaluation_get_model();
	$model_name = array();
	foreach($model as $key => $value){
		$model_name[$key] = $value['name'];
	}
	return $model_name;
}
?>
