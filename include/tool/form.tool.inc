<?php

function form($form_id, $model){
	if(function_exists('gridform_get_row_array')){
		head_add_js_array('gridRowArray', gridform_get_row_array());
	}
}

function form_render_grid($form_id, $name, $modelCol){
	require_once('gridform.tool.inc');
	return gridform_render($form_id, $name, $modelCol);
}
?>
