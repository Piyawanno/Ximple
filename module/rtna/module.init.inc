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

	include_once('Health.class.inc');
	$health = new Health();
	$health->initModule('Health.class.inc');

	include_once('PTTest.class.inc');
	$pttest = new PTTest();
	$pttest->initModule('PTTest.class.inc');

	include_once('Behavior.class.inc');
	$behavior = new Behavior();
	$behavior->initModule('Behavior.class.inc');

	include_once('LectureClass.class.inc');
	$lectureClass = new LectureClass();
	$lectureClass->initModule('LectureClass.class.inc');

	include_once('EducationYear.class.inc');
	$educationYear = new EducationYear();
	$educationYear->initModule('EducationYear.class.inc');

	include_once('ClassLog.class.inc');
	$classLog = new ClassLog();
	$classLog->initModule('Classlog.class.inc');

	include_once('Building.class.inc');
	$building = new Building();
	$building->initModule('Building.class.inc');

	include_once('Classroom.class.inc');
	$classroom = new Classroom();
	$classroom->initModule('Classroom.class.inc');

	include_once('Occupation.class.inc');
	$occupation = new Occupation();
	$occupation->initModule('Occupation.class.inc');

	$admin = new RoleManager('rtna_admin');
	$admin->setName('RTNA Database Administrator');
	$admin->setDescription('Who can manage all data in RTNA database.');
	$admin->submit();
	
	$cadetRTNA = new RoleManager('rtna_cadet');
	$cadetRTNA->setName('RTNA Cadet');
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
	$panel->append('rtna_cadet', 'List Cadet');
	$panel->append('rtna_officer_write', 'Create new Officer');
	$panel->append('rtna_officer', 'List Officer');
	$panel->append('rtna_faculty', 'Manage Faculty');
	$panel->append('rtna_yearserie', 'Manage Yearserie');
	$panel->append('rtna_belong', 'Manage Unit');
	$panel->append('rtna_club', 'Manage Club');
	$panel->append('rtna_activity', 'Manage Activity');
	$panel->append('rtna_health', 'Manage Health');
	$panel->append('rtna_pttest', 'Manage PT Test');
	$panel->append('rtna_behavior', 'Manage Behavior Indicator');
	$panel->append('rtna_building', 'Manage Building');
	$panel->append('rtna_classroom', 'Manage Classroom');
	$panel->append('rtna_educationYear', 'Manage Education Year');
	$panel->append('rtna_lectureClass', 'Manage Class');
	$panel->append('rtna_classLog', 'Manage Class Log');
	$panel->append('rtna_occupation', 'Manage Occupation');
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

	include_once('Health.class.inc');
	$health = new Health();
	$health->dropModule();

	include_once('PTTest.class.inc');
	$pttest = new PTTest();
	$pttest->dropModule();

	include_once('Behavior.class.inc');
	$behavior = new Behavior();
	$behavior->dropModule();

	include_once('LectureClass.class.inc');
	$lectureClass = new LectureClass();
	$lectureClass->dropModule();

	include_once('EducationYear.class.inc');
	$educationYear = new EducationYear();
	$educationYear->dropModule();

	include_once('ClassLog.class.inc');
	$classLog = new ClassLog();
	$classLog->dropModule();

	include_once('Building.class.inc');
	$building = new Building();
	$building->dropModule();

	include_once('Classroom.class.inc');
	$classroom = new Classroom();
	$classroom->dropModule();

	include_once('Occupation.class.inc');
	$occupation = new Occupation();
	$occupation->dropModule();

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
