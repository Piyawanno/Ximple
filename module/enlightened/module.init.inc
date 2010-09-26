<?php
function module_get_info_enlightened(){
	return array(
		'name' => 'Enlightened-Jurists',
		'description' => 'โมดูลสำหรับหน้าแรกของเวบไซท์ Enlightened-Jurists.com',
	);
}

function module_init_enlightened(){
	module_add('enlightened', 'enlightened.module.inc', 'Enlightened-Jurists');
}

function module_drop_enlightened(){
	module_drop('enlightened');
}
?>
