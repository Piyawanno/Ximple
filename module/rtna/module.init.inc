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

	include_once('YearSerie.class.inc');
	$yearSerie = new YearSerie();
	$yearSerie->initModule('YearSerie.class.inc');

	include_once('Faculty.class.inc');
	$faculty = new Faculty();
	$faculty->initModule('Faculty.class.inc');
	
	include_once('Club.class.inc');
	$club = new Club();
	$club->initModule('Club.class.inc');

	$admin = new RoleManager('rtna_admin');
	$admin->setName('RTNA Database Administrator');
	$admin->setDescription('Who can manage all data in RTNA database.');
	$admin->submit();

	$cadetDataManager = new RoleManager('rtna_cadet_data_manager');
	$cadetDataManager->setName('RTNA Cadet Data Manager');
	$cadetDataManager->setDescription('Who can add and edit data of Cadets.');
	$cadetDataManager->submit();

	$regimentOfficer = new RoleManager('rtna_regiment_officer');
	$regimentOfficer->setName('RTNA Regiment Officer');
	$regimentOfficer->setDescription('Who can edit own personal data.');
	$regimentOfficer->submit();

	$cadetRTNA = new RoleManager('rtna_cadet');
	$cadetRTNA->setName('Cadet of RTNA');
	$cadetRTNA->setDescription('Who can edit own personal data.');
	$cadetRTNA->submit();

	$panel = new PanelManager('RTNA Database');
	$panel->appendControl($cadet);
	$panel->appendControl($yearSerie);
	$panel->appendControl($faculty);
	$panel->append('rtna_cadet_write', 'Create new Cadet');
	$panel->append('rtna_cadet_list', 'List Cadet');
	$panel->append('rtna_faculty', 'Create new Faculty');
	$panel->appendRole($admin);
	$panel->appendRole($cadetDataManager);
	$panel->appendRole($cadetRTNA);
	$panel->submit();
}

function module_drop_rtna(){
	include_once('Cadet.class.inc');
	$cadet = new Cadet();
	$cadet->dropModule();

	include_once('YearSerie.class.inc');
	$yearSerie = new YearSerie();
	$yearSerie->dropModule();

	include_once('Faculty.class.inc');
	$faculty = new Faculty();
	$faculty->dropModule();
	
	include_once('Club.class.inc');
	$club = new Club();
	$club->dropModule();

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
