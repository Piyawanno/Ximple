<?php
function module_get_info_triamsob(){
	return array(
		'name' => tt('TriamSob'),
		'description' => tt('Frontpage module for TriamSob.Com')
	);
}

function module_init_triamsob(){
	module_add('triamsob', 'triamsob.module.inc', 'TriamSob');
}

function module_drop_triamsob(){
	module_drop('triamsob');
}
?>
