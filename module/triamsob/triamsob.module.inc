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
execute_add_function('triamsob_tutor_search_result');
execute_add_function('triamsob_tutor_subject');
execute_add_function('triamsob_tutor_subject_edit');
execute_add_function('triamsob_tutor_subject_save');
execute_add_function('triamsob_tutor_subject_icon');

define('TRIAMSOB_ADMISSION_CATEGORY', 4);
define('TRIAMSOB_SCHOLAR_CATEGORY', 6);
define('TRIAMSOB_EXERCISE_CATEGORY', 7);
define('TRIAMSOB_EXAM_CATEGORY', 8);
define('TRIAMSOB_TUTOR_CATEGORY', 9);
define('TRIAMSOB_STUDENT_CATEGORY', 10);

define('TRIAMSOB_WORD_WRAP', 3);
define('TRIAMSOB_TUTOR_GROUP', 4);
define('TRIAMSOB_PENDING_TUTOR_GROUP', 5);
define('TRIAMSOB_TUTOR_PER_PAGE', 10);

define('TRIAMSOB_SUBJECT_TYPE', 1);
define('TRIAMSOB_PLACE_TYPE', 2);
define('TRIAMSOB_PHONE_TYPE', 3);
define('TRIAMSOB_FACEBOOK_TYPE', 4);
define('TRIAMSOB_DEGREE_TYPE', 5);
define('TRIAMSOB_EXPERIENCE_TYPE', 6);
define('TRIAMSOB_ETC_TYPE', 7);

include('triamsob.tool.inc');

function triamsob(){
	head_add_css('triamsob.css');
	$journal = array(
		'admission' => triamsob_get_data(tt('Admission'), TRIAMSOB_ADMISSION_CATEGORY),
		'scholar' => triamsob_get_data(tt('Scholar'), TRIAMSOB_SCHOLAR_CATEGORY),
		'exercise' => triamsob_get_data(tt('Exercise'), TRIAMSOB_EXERCISE_CATEGORY),
		'exam' => triamsob_get_data(tt('Old Exam'), TRIAMSOB_EXAM_CATEGORY),
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
		'triamsob_tutor_list',
		'triamsob_tutor_profile',
		'triamsob_tutor_subject',
		'triamsob_tutor_search_result',
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
	include_once(ROOT_PATH.'module/registration/registration.module.inc');
	registration_save('triamsob_tutor_registration_confirm');
}

function triamsob_tutor_registration_confirm(){
	include_once(ROOT_PATH.'module/registration/registration.module.inc');
	$register_dir = ROOT_PATH.'files/registration/';
	$user = io_unserialize($register_dir.gg('key1'));
	if(is_array($user) and $user['key'] == gg('key2')){
		triamsob_insert_tutor($user);
		unlink($register_dir.gg('key1').'.php');
		execute_set_db();
		document_set_redirect('');
	}else{
		registration_error();
		execute_set_db();
		document_set_redirect('');
	}
}

function triamsob_tutor_article(){
	$clause = 'WHERE (publishing_status < 2 AND category='.TRIAMSOB_TUTOR_CATEGORY.') ';
	$clause.= 'ORDER BY publish_time DESC';
	return triamsob_list_block('journal', $clause);
}

function triamsob_student_article(){
	$clause = 'WHERE (publishing_status < 2 AND category='.TRIAMSOB_STUDENT_CATEGORY.') ';
	$clause.= 'ORDER BY publish_time DESC';
	return triamsob_list_block('journal', $clause);
}

function triamsob_tutor_list(){
	/// @TODO
	/// - sort tutor by review point.
	head_add_css('triamsob.css');
	document_set_path(tt('Tutor'), 'triamsob_tutor_list');
	$clause  = 'WHERE groups='.TRIAMSOB_TUTOR_GROUP.' GROUP BY users ORDER BY users';
	$uid = db_select_single_column('map', 'users', $clause, false);
	if(count($uid)){
		$clause = 'WHERE id='.join(' OR id=', $uid);
		return triamsob_render_tutor_list($clause, 'triamsob_tutor_list');
	}
}

function triamsob_tutor_profile(){
	search_set_page();
	head_add_css('triamsob.css');
	$user = userinfo_get_info_by_id(gg('id'));
	$user['subject'] = db_select_single_column('tutorsubject', 'subject', 'WHERE owner='.gg('id'));
	$user['subject_list'] = triamsob_get_tutor_subjects();
	$user['profile'] = userinfo_get_profile(gg('id'));
	document_set_path(tt('Tutor'), 'triamsob_tutor_list');
	document_set_path($user['login_name']);
	return render($user, 'tutorprofile.tpl', 'tutorprofile');
}

function triamsob_tutor_search_result(){
	/// @TODO
	/// - sort tutor by review point.
	$subject = pp('subject');
	if($subject == null) $subject = gg('subject');
	$place = pp('place');
	if($place == null) $place = gg('place');
	$etc = pp('etc');
	if($etc == null) $etc = gg('etc');
	
	$clause = 'WHERE subject='.$subject.' GROUP BY owner';
	$uid_subject = db_select_single_column('tutorsubject', 'owner', $clause);
	$clause = "WHERE profile LIKE '%".$place."%' AND profiletype=".TRIAMSOB_PLACE_TYPE;
	$uid_place = db_select_single_column('profile', 'owner', $clause);
	$clause = "WHERE profile LIKE '%".$etc."%'";
	$uid_profile = db_select_single_column('profile', 'owner', $clause);
	$uid = array_merge($uid_subject, $uid_place);
	$uid = array_merge($uid, $uid_profile);
	if(count($uid)){
		head_add_css('triamsob.css');
		document_set_path(tt('Tutor'), 'triamsob_tutor_list');
		document_set_path(tt('Search Tutor'));
		$clause = 'WHERE id='.join(' OR id=', $uid);
		$mode  = 'triamsob_tutor_search_result/';
		$mode .= 'subject/'.$subject.'/';
		$mode .= 'place/'.$place.'/';
		$mode .= 'etc/'.$etc.'/';
		return triamsob_render_tutor_list($clause, $mode);
	}
}

function triamsob_tutor_subject(){
	head_add_css('triamsob.css');
	$subject = triamsob_get_tutor_subjects();
	document_set_path(tt('Tutor'), 'triamsob_tutor_list');
	document_set_path(tt('Tutor for : ').$subject[gg('id')]);
	$clause = 'WHERE subject='.gg('id');
	$uid = db_select_single_column('tutorsubject', 'owner', $clause);
	if(count($uid)){
		$clause = 'WHERE id='.join(' OR id=', $uid);
		return triamsob_render_tutor_list($clause, 'triamsob_tutor_list');
	}
}

function triamsob_tutor_subject_icon($params, $result){
	if(authority_group('triamsob_tutor')){
		$result[] = array(
			'mode' => 'triamsob_tutor_subject_edit/'.$params['id'],
			'icon' => 'files/icon/edit.png',
			'label' => tt('Edit provided subject'),
		);
	}
	return $result;
}

function triamsob_tutor_subject_edit(){
	document_set_path(tt('User-Profile'), 'profile');
	$tutorSubject = triamsob_get_tutor_subject_obj();
	return $tutorSubject->edit();
}

function triamsob_tutor_subject_save(){
	$tutorSubject = triamsob_get_tutor_subject_obj();
	execute_set_db();
	document_set_redirect('triamsob_tutor_subject_edit/'.pp('owner'));
	return $tutorSubject->update();
}
?>
