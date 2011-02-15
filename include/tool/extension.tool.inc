<?php

function extension_execute($reference, $params=null){
	$extension = cc('extension');
	if(isset($extension[$reference])){
		$res = array();
		foreach($extension[$reference] as $key => $value){
			$res[] = execute_string($value, $params);
		}
		return $res;
	}
}

function extension_add($reference, $extension_name){
	$extension = cc('extension');
	if(!is_array($extension)){
		$extension = array();
	}
	if(!isset($extension[$reference])){
		$extension[$reference] = array();
	}
	if(!in_array($extension_name, $extension[$reference])){
		$extension[$reference][] = $extension_name;
	}
	config_set('extension', $extension);
}

function extension_drop($reference, $extension_name){
	$extension = cc('extension');
	if(!is_array($extension)){
		$extension = array();
	}
	if(isset($extension[$reference])){
		foreach($extension[$reference] as $key => $value){
			if($value == $extension_name){
				unset($extension[$reference][$key]);
				break;
			}
		}
	}
	config_set('extension', $extension);
}

?>
