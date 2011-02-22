<?php
function module_get_info_advertise(){
	return array(
		'name' => tt('Advertise'),
		'description' => tt('Module for Advertising and Customer management.')
	);
}

function module_init_advertise(){
	include_once('Advertise.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$advertise = new Advertise();
	$advertise->initModule('advertise.module.inc');
	
	module_add_role('advertise_admin', 'Advertise Administrator', 'Who can edit and drop advertise.');
	module_add_panel('Advertise', 'advertise_admin', 'advertise_write', 'create new Advertise');
	module_add_panel('Advertise', 'advertise_admin', 'advertise_list', 'list Advertise');
	module_add_panel('Advertise', 'advertise_admin', 'advertise_config', 'config Advertise');
	
	$path = ROOT_PATH.'files/advertise/';
	config_set('advertise_block_position', array(tt('Primaty Position')));
	if(!is_dir($path)) mkdir($path);
}

function module_drop_advertise(){
	include_once('Advertise.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$advertise = new Advertise();
	$advertise->dropModule();
	module_drop_role('advertise_admin');
	module_drop_panel('Advertise');
}
?>
