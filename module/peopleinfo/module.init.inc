<?php
function module_get_info_peopleinfo(){
	return array(
		'name' => tt('People Information Center'),
		'description' => tt('Database for People Information Center (PIC).')
	);
}

function module_init_peopleinfo(){
	include_once('People.class.inc');
	include_once('Event.class.inc');
	include_once('Information.class.inc');
	
	include_once('PeopleRelationModel.class.inc');
	include_once('PeopleFileModel.class.inc');
	include_once('EventRelationModel.class.inc');
	
	include_once(ROOT_PATH.'include/class/QuickTableCreator.class.inc');
	
	$people = new People();
	$people->initModule('peopleinfo.module.inc');
	$event = new Event();
	$event->createTable();
	$information = new Information();
	$information->createTable();
	
	$peopleRelationCreator = new QuickTableCreator('people_relation', new PeopleRelationModel());
	$peopleRelationCreator->create();
	
	$peopleFileCreator = new QuickTableCreator('people_file', new PeopleFileModel());
	$peopleFileCreator->create();
	
	$eventRelationCreator = new QuickTableCreator('event_relation', new EventRelationModel());
	$eventRelationCreator->create();
	
	module_add_role('peopleinfo_admin', 'People Information Administrator', 'Who manages all about People Information Center.');
	module_add_role('peopleinfo_observer', 'People Information Observer', 'Who observes all information in People Information Center.');
	module_add_role('peopleinfo_related', 'People Information Related', 'Who edit own information in People Information Center.');
	
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_event', 'event - show');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_event_list', 'event - manage');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_event_write', 'event - add');
	
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_info', 'information - show');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_info_list', 'information - manage');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_info_write', 'information - add');
	
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo', 'people - show');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_list', 'people - manage');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_write', 'people - add');
	
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_config', 'configuration PIC');
}

function module_drop_peopleinfo(){
	include_once('People.class.inc');
	$people = new People();
	$people->dropModule();
	module_drop('people');
	module_drop_role('peopleinfo_admin');
	module_drop_panel('People Information Center');
}
?>
