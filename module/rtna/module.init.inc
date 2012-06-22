<?php
function module_get_info_rtna(){
	return array(
		'name' => tt('RTNA Database'),
		'description' => tt('Database Management for Royal Thai Naval Academy(RTNA)')
	);
}

function module_init_rtna(){
	include_once('Cadet.class.inc');
	$cadet = new Cadet();
	$cadet->initModule('Cadet.class.inc');
	
	$admin = new RoleManager('rtna_admin');
	$admin->setName('RTNA Database Administrator');
	$admin->setDescription('Who can manage all data in RTNA database.');
	$admin->submit();

	$cadetDataManager = new RoleManager('rtna_cadet_data_manager');
	$cadetDataManager->setName('RTNA Cadet Data Manager');
	$cadetDataManager->setDescription('Who can add and edit data of Cadets.');
	$cadetDataManager->submit();
}

function module_drop_rtna(){
	include_once('Cadet.class.inc');
	$cadet = new Cadet();
	$cadet->dropModule();
	
	$admin = new RoleManager('rtna_admin');
	$admin->drop();

	$cadetDataManager = new RoleManager('rtna_cadet_data_manager');
	$cadetDataManager->drop();
}
?>
