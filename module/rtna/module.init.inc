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
	
	include_once('Officer.class.inc');
	$officer = new Officer();
	$officer->initModule('Officer.class.inc');

	include_once('YearSerie.class.inc');
	$yearSerie = new YearSerie();
	$yearSerie->initModule('YearSerie.class.inc');

	include_once('Faculty.class.inc');
	$faculty = new Faculty();
	$faculty->initModule('Faculty.class.inc');
	
	include_once('Club.class.inc');
	$club = new Club();
	$club->initModule('Club.class.inc');

	include_once('Belong.class.inc');
	$belong = new Belong();
	$belong->initModule('Belong.class.inc');

	include_once('Activity.class.inc');
	$activity = new Activity();
	$activity->initModule('Activity.class.inc');

	$admin = new RoleManager('rtna_admin');
	$admin->setName('RTNA Database Administrator');
	$admin->setDescription('Who can manage all data in RTNA database.');
	$admin->submit();
	
	$cadetRTNA = new RoleManager('rtna_cadet');
	$cadetRTNA->setName('Cadet of RTNA');
	$cadetRTNA->setDescription('Who can edit own personal data.');
	$cadetRTNA->submit();

	$cadetDataManager = new RoleManager('rtna_cadet_data_manager');
	$cadetDataManager->setName('RTNA Cadet Data Manager');
	$cadetDataManager->setDescription('Who can add and edit data of Cadets.');
	$cadetDataManager->submit();

	$officerRTNA = new RoleManager('rtna_officer');
	$officerRTNA->setName('RTNA Officer');
	$officerRTNA->setDescription('Who can edit own personal data.');
	$officerRTNA->submit();

	$officerDataManager = new RoleManager('rtna_officer_data_manager');
	$officerDataManager->setName('RTNA Officer Data Manager');
	$officerDataManager->setDescription('Who can add and edit data of Officer.');
	$officerDataManager->submit();
	
	$belongDataManager = new RoleManager('rtna_belong_data_manager');
	$belongDataManager->setName('RTNA Officer Data Manager');
	$belongDataManager->setDescription('Who can add and edit data of Unit.');
	$belongDataManager->submit();
	
	$panel = new PanelManager('RTNA Database');
	$panel->appendControl($cadet);
	$panel->appendControl($officer);
	$panel->appendControl($yearSerie);
	$panel->appendControl($faculty);
	$panel->appendControl($belong);
	$panel->append('rtna_cadet_write', 'Create new Cadet');
	$panel->append('rtna_cadet_list', 'List Cadet');
	$panel->append('rtna_officer_write', 'Create new Officer');
	$panel->append('rtna_officer_list', 'List Officer');
	$panel->append('rtna_faculty', 'Create new Faculty');
	$panel->append('rtna_yearserie', 'Create new Yearserie');
	$panel->append('rtna_belong', 'Create new Unit');
	$panel->appendRole($admin);
	$panel->appendRole($cadetDataManager);
	$panel->appendRole($cadetRTNA);
	$panel->appendRole($officerDataManager);
	$panel->appendRole($belongDataManager);
	$panel->appendRole($officerRTNA);
	$panel->submit();
}

function module_drop_rtna(){
	include_once('Cadet.class.inc');
	$cadet = new Cadet();
	$cadet->dropModule();
	
	include_once('Officer.class.inc');
	$officer = new Officer();
	$officer->dropModule();

	include_once('YearSerie.class.inc');
	$yearSerie = new YearSerie();
	$yearSerie->dropModule();

	include_once('Faculty.class.inc');
	$faculty = new Faculty();
	$faculty->dropModule();
	
	include_once('Club.class.inc');
	$club = new Club();
	$club->dropModule();

	include_once('Belong.class.inc');
	$belong = new Belong();
	$belong->dropModule();

	include_once('Activity.class.inc');
	$activity = new Activity();
	$activity->dropModule();

	$admin = new RoleManager('rtna_admin');
	$admin->drop();

	$cadetDataManager = new RoleManager('rtna_cadet_data_manager');
	$cadetDataManager->drop();

	$regimentOfficer = new RoleManager('rtna_regiment_officer');
	$regimentOfficer->drop();

	$cadetRTNA = new RoleManager('rtna_cadet');
	$cadetRTNA->drop();
	
	$panel = new PanelManager('RTNA Database');
	$panel->drop();

	
}
?>
