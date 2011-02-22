<?php
execute_add_function('triamsob');
execute_add_function('triamsob_tutor_registration');
execute_add_function('triamsob_tutor_registration_save');
execute_add_function('triamsob_tutor_registration_confirm');
execute_add_function('triamsob_tutor_list');
execute_add_function('triamsob_tutor_profile');
execute_add_function('triamsob_render_content_box');
execute_add_function('triamsob_student_article');
execute_add_function('triamsob_tutor_article');
execute_add_function('triamsob_tutorialschool_article');

define('TRIAMSOB_ADMISSION_CATEGORY', 1);
define('TRIAMSOB_SCHOLAR_CATEGORY', 3);
define('TRIAMSOB_EXERCISE_CATEGORY', 4);
define('TRIAMSOB_EXAM_CATEGORY', 2);
define('TRIAMSOB_TUTOR_CATEGORY', 5);
define('TRIAMSOB_STUDENT_CATEGORY', 6);
define('TRIAMSOB_WORD_WRAP', 3);
define('TRIAMSOB_PENDING_TUTOR_GROUP', 3);
define('TRIAMSOB_TUTOR_GROUP', 4);
define('TRIAMSOB_TUTOR_PER_PAGE', 10);

include('triamsob.tool.inc');

function triamsob(){
	head_add_css('triamsob.css');
	$journal = array(
		'admission' => triamsob_get_data(tt('Admission'), TRIAMSOB_ADMISSION_CATEGORY),
		'scholar' => triamsob_get_data(tt('Scholar'), TRIAMSOB_SCHOLAR_CATEGORY),
		'exercise' => triamsob_get_data(tt('Exercise'), TRIAMSOB_EXERCISE_CATEGORY),
		'exam' => triamsob_get_data(tt('Old Exam'), TRIAMSOB_EXERCISE_CATEGORY),
	);
	$clause = 'WHERE section='.SECTION.' ORDER BY comment_time DESC LIMIT 5';
	$last_commented_forum = db_select_single_column('forum_entry', 'topic', $clause);
	$clause = 'WHERE section='.SECTION.' ORDER BY id DESC LIMIT 5';
	$last_posted_forum = db_select_single_column('forum_entry', 'topic', $clause);
	$render_array = array(
		'journal' => $journal,
		'last_commented_forum' => $last_commented_forum,
		'last_posted_forum' => $last_posted_forum,
		'category' => triamsob_get_category(),
	);
	return render($render_array, 'triamsob.tpl', 'triamsob');
}

function triamsob_render_content_box($param, $body){
	$exeption_mode = array(
		'triamsob',
	);
	if(MODULE == 'forum'){
		$body = triamsob_render_box($body, null, 'forum_box');
	}elseif(!in_array(MODE, $exeption_mode)){
		$body = triamsob_render_box($body);
	}
	return $body;
}

function triamsob_render_box($body, $head=null, $class='main_box'){
	if($head!=null){
		$head = '<h3 class="title_label">'.$head.'</h3>';
	}
	return '
	<div class="'.$class.'">
		<div class="'.$class.'_head"></div>
		<div class="'.$class.'_body">
			<div class="'.$class.'_content">
				'.$head.'
				'.$body.'
			</div>
		</div>
		<div class="'.$class.'_foot"></div>
	</div>';
}

function triamsob_tutor_registration(){
	include('TutorRegistration.class.inc');
	$registration = new TutorRegistration();
	document_set_path(tt('Tutor'), 'triamsob_tutor_list');
	document_set_path(tt('Tutor Registration'));
	return $registration->registration();
}

function triamsob_tutor_registration_save(){
	include_once(ROOT_PATH.'module/registration/registration.tool.inc');
	registration_confirm('triamsob_tutor_registration_confirm');
}

function triamsob_tutor_registration_confirm(){
	include_once(ROOT_PATH.'module/registration/registration.module.inc');
	$uid = registration_confirm();
	$data = array(
		'users' => $uid,
		'groups' => TRIAMSOB_PENDING_TUTOR_GROUP,
		'section' => SECTION,
	);
	db_insert('map', $data);
}

function triamsob_tutor_list(){
	/// @TODO
	/// - sort tutor by review point.
	/// - render page.
	/// - show by tag.
	document_set_path(tt('Tutor'), 'triamsob_tutor_list');
	
	$clause  = 'WHERE groups='.TRIAMSOB_TUTOR_GROUP.' ORDER BY users ';
	$clause .= 'LIMIT '.TRIAMSOB_TUTOR_PER_PAGE.' OFFSET '.TRIAMSOB_TUTOR_PER_PAGE*MODE_PAGE;
	$uid = db_select_single_column('map', 'users', $clause, false);
	if(count($uid)){
		$column = array('id', 'login_name', 'email', 'avatar', 'space_used');
		$clause = 'WHERE id='.join(' OR id=', $uid);
		$users = db_select('users', $column, $clause);
	
		$column = array('id', 'owner', 'profile', 'profiletype');
		$clause = 'WHERE owner='.join(' OR owner=', $uid);
		$profile = db_select('profile', $column, $clause);
	
		foreach($profile as $key => $value){
			$users[$value['owner']]['profile'][$value['profiletype']] = $value['profile'];
		}
	}
}

function triamsob_tutor_profile(){

}
?>
