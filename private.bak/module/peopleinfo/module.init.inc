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
	include_once('PeopleDataModel.class.inc');
	include_once('PeopleFileModel.class.inc');
	include_once('EventRelationModel.class.inc');
	include_once('PeopleConfig.class.inc');
	include_once('DataReport.class.inc');
	include_once('PeopleUser.class.inc');
	include_once(INCLUDE_PATH.'class/QuickTableCreator.class.inc');
	
	$people = new People();
	$people->initModule('People.class.inc');
	
	$event = new Event();
	$event->initModule('Event.class.inc');
	
	$information = new Information();
	$information->initModule('Information.class.inc');
	
	$peopleConfig = new PeopleConfig();
	$peopleConfig->initModule('PeopleConfig.class.inc');
	
	$dataReport = new DataReport();
	$dataReport->initModule('DataReport.class.inc');
	
	$peopleUser = new PeopleUser();
	$peopleUser->initModule('PeopleUser.class.inc');
	
	$peopleRelationCreator = new QuickTableCreator(new PeopleRelationModel());
	$peopleRelationCreator->create();
	
	$peopleDataCreator = new QuickTableCreator(new PeopleDataModel());
	$peopleDataCreator->create();
	
	$peopleFileCreator = new QuickTableCreator(new PeopleFileModel());
	$peopleFileCreator->create();
	
	$eventRelationCreator = new QuickTableCreator(new EventRelationModel());
	$eventRelationCreator->create();
	
	module_add_role('peopleinfo_admin', 'People Information Administrator', 'Who manages all about People Information Center.');
	module_add_role('peopleinfo_informant', 'People Information Informant', 'Who observes, contributes information and edit own information People Information Center.');
	module_add_role('peopleinfo_observer', 'People Information Observer', 'Who observes all information in People Information Center.');
	module_add_role('peopleinfo_related', 'People Information Related', 'Who edit own information in People Information Center.');
	
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_event', 'event');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_info', 'information');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo', 'people');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_tag_clound', 'tag clound');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_config', 'configuration');
	module_add_panel('People Information Center', 'peopleinfo_admin', 'peopleinfo_report', 'report');
	
	module_add_panel('People Information Center', 'peopleinfo_informant', 'peopleinfo_event', 'event');
	module_add_panel('People Information Center', 'peopleinfo_informant', 'peopleinfo_info', 'information');
	module_add_panel('People Information Center', 'peopleinfo_informant', 'peopleinfo', 'people');
	module_add_panel('People Information Center', 'peopleinfo_informant', 'peopleinfo_tag_clound', 'tag clound');
	
	module_add_panel('People Information Center', 'peopleinfo_observer', 'peopleinfo_event', 'event');
	module_add_panel('People Information Center', 'peopleinfo_observer', 'peopleinfo_info', 'information');
	module_add_panel('People Information Center', 'peopleinfo_observer', 'peopleinfo', 'people');
	module_add_panel('People Information Center', 'peopleinfo_observer', 'peopleinfo_tag_clound', 'tag clound');
	module_add_panel('People Information Center', 'peopleinfo_observer', 'peopleinfo_report', 'report');
	
	if(count(cc('peopleinfo_related')) == 0){
		notify_add_warning(peopleinfo_get_group_warning());
	}
	
	if(!is_dir(FILES_PATH.'peopleinfo/')){
		mkdir(FILES_PATH.'peopleinfo/');
	}
	
	config_set('peopleinfo_data_type', peopleinfo_get_default_datat_type());
}

function module_drop_peopleinfo(){
	include_once('People.class.inc');
	include_once('Event.class.inc');
	include_once('Information.class.inc');
	include_once('PeopleConfig.class.inc');
	include_once('PeopleUser.class.inc');
	
	$people = new People();
	$people->dropModule();
	
	$event = new Event();
	$event->dropModule();
	
	$information = new Information();
	$information->dropModule();
	
	$peopleConfig = new PeopleConfig();
	$peopleConfig->dropModule();
	
	$peopleUser = new PeopleUser();
	$peopleUser->dropModule();
	
	module_drop('people');
	module_drop_role('peopleinfo_admin');
	module_drop_panel('People Information Center');
}
?>
