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

function triamsob_render_category_link($category, $cid, $mode){
	$structured = array(
		 'id' => $cid,
		 'category' => $category,
	);
	$translated = translate_content($structured, 'category', $cid);
	$label = $translated['category'];
	return '<a href="'.SECTION_URI.Q.$mode.'/tag/'.$category.'/tag_label/'.$label.'">'.tt('read more').'</a>';
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
?>
