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

	include_once('Subject.class.inc');
	$subject = new Subject();
	$subject->initModule('Subject.class.inc');

	include_once('Bedroom.class.inc');
	$bedroom = new Bedroom();
	$bedroom->initModule('Bedroom.class.inc');

	include_once('Exam.class.inc');
	$exam = new Exam();
	$exam->initModule('Exam.class.inc');

	include_once('ExamType.class.inc');
	$examType = new ExamType();
	$examType->initModule('ExamType.class.inc');

	$admin = new RoleManager('rtna_admin');
	$admin->setName('RTNA Database Administrator');
	$admin->setDescription('Who can manage all data in RTNA database.');
	$admin->submit();
	
	$cadetRTNA = new RoleManager('rtna_cadet');
	$cadetRTNA->setName('RTNA Cadet');
	$cadetRTNA->setDescription('Who can edit own personal data.');
	$cadetRTNA->submit();

	$officerRTNA = new RoleManager('rtna_officer');
	$officerRTNA->setName('RTNA Officer');
	$officerRTNA->setDescription('Who can edit own personal data.');
	$officerRTNA->submit();

	$officerRegiment = new RoleManager('rtna_regiment_officer');
	$officerRegiment->setName('RTNA Regiment Officer');
	$officerRegiment->setDescription('Who can edit own personal data.');
	$officerRegiment->submit();

	$activityManager = new RoleManager('rtna_activity_manager');
	$activityManager->setName('RTNA Activity Manager');
	$activityManager->setDescription('Who can add and edit data of activity.');
	$activityManager->submit();

	$bedroomDataManager = new RoleManager('rtna_bedroom_data_manager');
	$bedroomDataManager->setName('RTNA Bedroom Data Manager');
	$bedroomDataManager->setDescription('Who can add and edit bedroom data of cadet.');
	$bedroomDataManager->submit();

	$behaviorManager = new RoleManager('rtna_behavior_manager');
	$behaviorManager->setName('RTNA Behavior Manager');
	$behaviorManager->setDescription('Who can add and edit data of behavior.');
	$behaviorManager->submit();

	$belongDataManager = new RoleManager('rtna_belong_data_manager');
	$belongDataManager->setName('RTNA Officer Data Manager');
	$belongDataManager->setDescription('Who can add and edit data of Unit.');
	$belongDataManager->submit();

	$buildingManager = new RoleManager('rtna_building_manager');
	$buildingManager->setName('RTNA Building Manager');
	$buildingManager->setDescription('Who can add and edit data of Building.');
	$buildingManager->submit();

	$cadetDataManager = new RoleManager('rtna_cadet_data_manager');
	$cadetDataManager->setName('RTNA Cadet Data Manager');
	$cadetDataManager->setDescription('Who can add and edit data of Cadets.');
	$cadetDataManager->submit();

	$classlogManager = new RoleManager('rtna_classlog_manager');
	$classlogManager->setName('RTNA Classlog Manager');
	$classlogManager->setDescription('Who can add and edit data of Classlog.');
	$classlogManager->submit();

	$classroomManager = new RoleManager('rtna_classroom_manager');
	$classroomManager->setName('RTNA Classroom Manager');
	$classroomManager->setDescription('Who can add and edit data of Classroom.');
	$classroomManager->submit();

	$clubManager = new RoleManager('rtna_club_manager');
	$clubManager->setName('RTNA Cadet Club Manager');
	$clubManager->setDescription('Who can add and edit club of cadet.');
	$clubManager->submit();

	$educationYearManager = new RoleManager('rtna_education_year_manager');
	$educationYearManager->setName('RTNA Education Year Manager');
	$educationYearManager->setDescription('Who can add and edit data of education year.');
	$educationYearManager->submit();

	$examDataManager = new RoleManager('rtna_exam_data_manager');
	$examDataManager->setName('RTNA Exam Data Manager');
	$examDataManager->setDescription('Who can add and edit exam data of cadet.');
	$examDataManager->submit();

	$facultyManager = new RoleManager('rtna_faculty_manager');
	$facultyManager->setName('RTNA Faculty Manager');
	$facultyManager->setDescription('Who can add and edit data of faculty.');
	$facultyManager->submit();

	$healthDataManager = new RoleManager('rtna_health_data_manager');
	$healthDataManager->setName('RTNA Health Data Manager');
	$healthDataManager->setDescription('Who can add and edit health data of cadet.');
	$healthDataManager->submit();

	$lectureClassManager = new RoleManager('rtna_lecture_class_manager');
	$lectureClassManager->setName('RTNA Lecture Class Manager');
	$lectureClassManager->setDescription('Who can add and edit data of lecture class.');
	$lectureClassManager->submit();

	$subjectManager = new RoleManager('rtna_subject_manager');
	$subjectManager->setName('RTNA Subject Manager');
	$subjectManager->setDescription('Who can add and edit subject.');
	$subjectManager->submit();

	$officerDataManager = new RoleManager('rtna_officer_data_manager');
	$officerDataManager->setName('RTNA Officer Data Manager');
	$officerDataManager->setDescription('Who can add and edit data of Officer.');
	$officerDataManager->submit();

	$ptTestDataManager = new RoleManager('rtna_pttest_data_manager');
	$ptTestDataManager->setName('RTNA PT Test Data Manager');
	$ptTestDataManager->setDescription('Who can add and edit data of PT Test.');
	$ptTestDataManager->submit();

	$yearSerieDataManager = new RoleManager('rtna_yearserie_data_manager');
	$yearSerieDataManager->setName('RTNA Yearserie Data Manager');
	$yearSerieDataManager->setDescription('Who can add and edit Yearserie of cadet.');
	$yearSerieDataManager->submit();
	
	$panel = new PanelManager(tt('RTNA Database'));
	$panel->appendControl($cadet);
	$panel->appendControl($officer);
	$panel->appendControl($yearSerie);
	$panel->appendControl($faculty);
	$panel->appendControl($belong);
	$panel->appendControl($club);
	$panel->appendControl($activity);
	$panel->appendControl($health);
	$panel->appendControl($pttest);
	$panel->appendControl($behavior);
	$panel->appendControl($lectureClass);
	$panel->appendControl($educationYear);
	$panel->appendControl($classLog);
	$panel->appendControl($building);
	$panel->appendControl($classroom);
	$panel->appendControl($subject);
	$panel->appendControl($bedroom);
	$panel->appendControl($exam);
	$panel->append('rtna_cadet', tt('Manage Cadet'));
	$panel->append('rtna_officer', tt('Manage Officer'));
	$panel->append('rtna_faculty', tt('Manage Faculty'));
	$panel->append('rtna_yearserie', tt('Manage Year Serie'));
	$panel->append('rtna_belong', tt('Manage Unit'));
	$panel->append('rtna_club', tt('Manage Club'));
	$panel->append('rtna_activity', tt('Manage Activity'));
	$panel->append('rtna_health', tt('Manage Health'));
	$panel->append('rtna_pttest', tt('Manage PT Test'));
	$panel->append('rtna_behavior', tt('Manage Behavior Indicator'));
	$panel->append('rtna_building', tt('Manage Building'));
	$panel->append('rtna_classroom', tt('Manage Classroom'));
	$panel->append('rtna_educationYear', tt('Manage Education Year'));
	$panel->append('rtna_lectureClass', tt('Manage Class'));
	$panel->append('rtna_classLog', tt('Manage Class Log'));
	$panel->append('rtna_classLog', tt('Manage Classroom'));
	$panel->append('rtna_subject', tt('Manage Subject'));
	$panel->append('rtna_exam', tt('Manage Exam'));
	$panel->appendRole($admin);
	$panel->appendRole($cadetRTNA);
	$panel->appendRole($officerRTNA);
	$panel->appendRole($officerRegiment);
	$panel->appendRole($activityManager);
	$panel->appendRole($bedroomDataManager);
	$panel->appendRole($behaviorManager);
	$panel->appendRole($belongDataManager);
	$panel->appendRole($buildingManager);
	$panel->appendRole($cadetDataManager);
	$panel->appendRole($classlogManager);
	$panel->appendRole($classroomManager);
	$panel->appendRole($clubManager);
	$panel->appendRole($educationYearManager);
	$panel->appendRole($facultyManager);
	$panel->appendRole($healthDataManager);
	$panel->appendRole($lectureClassManager);
	$panel->appendRole($subjectManager);
	$panel->appendRole($officerDataManager);
	$panel->appendRole($ptTestDataManager);
	$panel->appendRole($yearSerieDataManager);
	$panel->appendRole($examDataManager);
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

	include_once('Subject.class.inc');
	$subject = new Subject();
	$subject->dropModule();

	include_once('Bedroom.class.inc');
	$bedroom = new Bedroom();
	$bedroom->dropModule();

	include_once('Exam.class.inc');
	$exam = new Exam();
	$exam->dropModule();

	include_once('ExamType.class.inc');
	$examType = new ExamType();
	$examType->dropModule();

	$admin = new RoleManager('rtna_admin');
	$admin->drop();

	$cadetRTNA = new RoleManager('rtna_cadet');
	$cadetRTNA->drop();

	$officerRTNA = new RoleManager('rtna_officer');
	$officerRTNA->drop();

	$officerRegiment = new RoleManager('rtna_regiment_officer');
	$officerRegiment->drop();

	$activityManager = new RoleManager('rtna_activity_manager');
	$activityManager->drop();

	$bedroomDataManager = new RoleManager('rtna_bedroom_data_manager');
	$bedroomDataManager->drop();

	$behaviorManager = new RoleManager('rtna_behavior_manager');
	$behaviorManager->drop();

	$belongDataManager = new RoleManager('rtna_belong_data_manager');
	$belongDataManager->drop();

	$buildingManager = new RoleManager('rtna_building_manager');
	$buildingManager->drop();

	$cadetDataManager = new RoleManager('rtna_cadet_data_manager');
	$cadetDataManager->drop();

	$classlogManager = new RoleManager('rtna_classlog_manager');
	$classlogManager->drop();

	$classroomManager = new RoleManager('rtna_classroom_manager');
	$classroomManager->drop();

	$clubManager = new RoleManager('rtna_club_manager');
	$clubManager->drop();

	$educationYearManager = new RoleManager('rtna_education_year_manager');
	$educationYearManager->drop();

	$examDataManager = new RoleManager('rtna_exam_data_manager');
	$examDataManager->drop();

	$facultyManager = new RoleManager('rtna_faculty_manager');
	$facultyManager->drop();

	$healthDataManager = new RoleManager('rtna_health_data_manager');
	$healthDataManager->drop();

	$lectureClassManager = new RoleManager('rtna_lecture_class_manager');
	$lectureClassManager->drop();
	
	$subjectManager = new RoleManager('rtna_subject_manager');
	$subjectManager->drop();

	$officerDataManager = new RoleManager('rtna_officer_data_manager');
	$officerDataManager->drop();

	$ptTestDataManager = new RoleManager('rtna_pttest_data_manager');
	$ptTestDataManager->drop();

	$yearSerieDataManager = new RoleManager('rtna_yearserie_data_manager');
	$yearSerieDataManager->drop();

	$panel = new PanelManager('RTNA Database');
	$panel->drop();

}
?>
