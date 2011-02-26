<?php
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

function triamsob_list_block($table, $clause){
	$clause = $clause.' LIMIT 5';
	$item = db_select_single_column($table, 'topic', $clause);
	$render_array = array(
		'mode' => $table,
		'item' => $item,
	);
	return render($render_array, 'module/flashblock/theme/flashblock.tpl', 'flashblock');
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

function triamsob_get_tutor_subject_obj(){
	if(authority_group('triamsob_tutor')){
		include('TutorSubject.class.inc');
		return new TutorSubject();
	}else{
		error_denied();
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
