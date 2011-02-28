<?php

function triamsob_define_constant(){
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
}

function triamsob_add_execute(){
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
	execute_add_function('triamsob_tutor_subject_icon');
}

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

function triamsob_get_data($label, $refernce){
	$p  = "WHERE category=%d AND publishing_status < 2 AND publish_time < '".NOW;
	$p .= "' ORDER BY publish_time DESC LIMIT 5";
	$column = array('id', 'topic', 'uri', 'intro', 'icon');
	return array(
		'label' => $label,
		'data' => db_select('journal', $column, sprintf($p, $refernce)),
		'category' => $refernce,
	);
}

function triamsob_get_category(){
	$clause = 'WHERE id='.TRIAMSOB_ADMISSION_CATEGORY.' OR ';
	$clause.= 'id='.TRIAMSOB_SCHOLAR_CATEGORY.' OR ';
	$clause.= 'id='.TRIAMSOB_EXERCISE_CATEGORY.' OR ';
	$clause.= 'id='.TRIAMSOB_EXAM_CATEGORY;
	$category = db_select_single_column('category', 'category', $clause);
	
	if(!isset($category[TRIAMSOB_ADMISSION_CATEGORY])){
		$category[TRIAMSOB_ADMISSION_CATEGORY] = null;
	}
	if(!isset($category[TRIAMSOB_SCHOLAR_CATEGORY])){
		$category[TRIAMSOB_SCHOLAR_CATEGORY] = null;
	}
	if(!isset($category[TRIAMSOB_EXERCISE_CATEGORY])){
		$category[TRIAMSOB_EXERCISE_CATEGORY] = null;
	}
	if(!isset($category[TRIAMSOB_EXAM_CATEGORY])){
		$category[TRIAMSOB_EXAM_CATEGORY] = null;
	}
	return $category;
}

function triamsob_render_category_link($category, $cid, $mode, $content){
	$structured = array(
		 'id' => $cid,
		 'category' => $category,
	);
	$translated = translate_content($structured, 'category', $cid);
	$label = $translated['category'];
	return '<a href="'.SECTION_URI.Q.$mode.'/tag/'.$category.'/tag_label/'.$label.'">'.$content.'</a>';
}

function triamsob_wrap_paragraph($content){
	$content = strip_tags($content);
	$splitted = explode(' ', $content);
	$wrapped = '';
	for($i=0; $i<TRIAMSOB_WORD_WRAP; $i++){
		$wrapped .= $splitted[$i].' ';
	}
	return $wrapped.' ...';
}

function triamsob_get_tutor_subjects(){
	return array(
		0 => 'คณิต ประถม',
		1 => 'คณิต ม.ต้น ',
		2 => 'คณิต ม.ปลาย',
		3 => 'อังกฤษ ประถม',
		4 => 'อังกฤษ ม.ต้น ',
		5 => 'อังกฤษ ม.ปลาย',
		6 => 'ฟิสิกส์',
		7 => 'เคมี',
		8 => 'ชีวะ',
		9 => 'วิทยาศาสตร์ ประถม',
		10 => 'วิทยาศาสตร์ ม.ต้น',
		11 => 'วิทยาศาสตร์ ม.ปลาย',
		12 => 'ไทย',
		13 => 'สังคม',
		14 => 'อื่นๆ',
	);
}

function triamsob_render_tutor_list($clause, $mode){
	include_once(ROOT_PATH.'include/class/PagerRender.class.inc');
	$rows_number = db_get_rows_number('users', $clause);
	$users = triamsob_get_tutor_info($clause);
	$pager = new PagerRender(TRIAMSOB_TUTOR_PER_PAGE, $rows_number);
	$render_array = array(
		'users' => $users,
		'subject' => triamsob_get_tutor_subjects(),
	);
	$render = render($render_array, 'tutorprofilelist.tpl', 'tutorprofilelist');
	return $render.$pager->render($mode);
}

function triamsob_get_tutor_info($clause){
	$clause .= ' LIMIT '.TRIAMSOB_TUTOR_PER_PAGE.' OFFSET '.TRIAMSOB_TUTOR_PER_PAGE*MODE_PAGE;
	$column = array('id', 'login_name', 'email', 'avatar', 'space_used');
	$users = db_select('users', $column, $clause);
	foreach($users as $key => $value){
		if(strlen($value['avatar']) == 0){
			$users[$key]['avatar'] = 'files/default.png';
		}
	}
	$users = triamsob_get_tutor_profile($users);
	$users = triamsob_get_tutor_subject($users);
	return $users;
}

function triamsob_get_tutor_profile($users){
	$uid = array_keys($users);
	$column = array('id', 'owner', 'profile', 'profiletype');
	$clause = 'WHERE owner='.join(' OR owner=', $uid);
	$profile = db_select('profile', $column, $clause);
	foreach($profile as $key => $value){
		$users[$value['owner']]['profile'][$value['profiletype']] = $value['profile'];
	}
	return $users;
}

function triamsob_render_profile_item($profile, $type, $label){
	if(isset($profile[$type])){
		return '<p>
					<label> '.$label.': </label>
					'.$profile[$type].'
				</p>';
	}
}

function triamsob_render_profile_descriptive_item($profile, $type, $label){
	if(isset($profile[$type])){
		return '<p><label> '.$label.': </label></p>
				<p>
					'.$profile[$type].'
				</p>';
	}
}

function triamsob_insert_tutor($user){
	$user['login_name_hash'] = sha1($user['login_name']);
	$subject = $user['subject'];
	unset($user['key']);
	unset($user['subject']);
	$uid = db_insert('users', $user);
	$p = tt('Congratulation and welcome to %s. Your registration is completed.');
	notify_add_info(sprintf($p, cc('section_name')));
	triamsob_insert_tutor_subject($uid, $subject);
}

function triamsob_insert_tutor_subject($uid, $subject){
	$data = array(
		'users' => $uid,
		'groups' => TRIAMSOB_PENDING_TUTOR_GROUP,
		'section' => SECTION,
	);
	db_insert('map', $data);
	$data = array('owner' => $uid);
	if(is_array($subject)){
		foreach($subject as $key => $value){
			$data['subject'] = (int) $value;
			db_insert('tutorsubject', $data);
		}
	}
}

function triamsob_get_tutor_subject($tutors){
	$uid = array_keys($tutors);
	$clause = 'WHERE owner='.join(' OR owner=', $uid);
	$subject = db_select('tutorsubject', array('owner', 'subject'), $clause);
	foreach($tutors as $uid => $user){
		$tutors[$uid]['subject'] = array();
	}
	foreach($subject as $key => $value){
		$tutors[$value['owner']]['subject'][] = $value['subject'];
	}
	return $tutors;
}
?>
