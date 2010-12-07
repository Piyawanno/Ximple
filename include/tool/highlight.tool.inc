<?php

function highlight($content){
	$code_array = highlight_getcode($content);
	foreach($code_array as $key => $value){
		$hightlighted = highlight_execute($value);
		$content = str_replace($key, $hightlighted, $content);
	}
	return $content;
}

function highlight_getcode($content){
	
}

function highlight_execute($code){
	
}

?>
