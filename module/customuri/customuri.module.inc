<?php
require_once('CustomURI.class.inc');
execute_add_function('customuri_map');
execute_add_function('customuri_post_render');

function customuri_map(){
	$called_uri = substr(vv('QUERY_STRING'), 1);
	$clause = "WHERE mapped_URI='$called_uri' AND section=".SECTION;
	$data = db_select_single_column('customuri', 'original_URI', $clause, false);
	if(count($data)){
		$_GET = array('/'.$data[0] => '');
		$_SERVER['QUERY_STRING'] = '/'.$data[0]; 
	}
}

function customuri_post_render($render){
	if(!document_has_form()){
		$clause = "WHERE section=".SECTION;
		$data = db_select('customuri', array('original_URI', 'mapped_URI'), $clause);
		foreach($data as $key => $value){
			$original = '"'.SECTION_URI.$value['original_URI'].'"';
			$mapped = '"'.SECTION_URI.$value['mapped_URI'].'"';
			$render = str_replace($original, $mapped, $render);
		}
	}
	return $render;
}
?>
