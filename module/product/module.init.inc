<?php
function module_get_info_product(){
	return array();
}


function module_init_product(){
	config_set('product_type_icon_size', 64);
	$directory = FILES_PATH.'product/';
	if(!is_dir($directory)) mkdir($directory);
	$directory .= SECTION.'/';
	if(!is_dir($directory)) mkdir($directory);
	$directory .= 'typeicon/';
	if(!is_dir($directory)) mkdir($directory);
}

function module_drop_product(){

}
?>
