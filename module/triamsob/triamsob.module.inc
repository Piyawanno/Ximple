<?php
execute_add_function('triamsob');
define('TRIAMSOB_ADMISSION_CATEGORY', 1);
define('TRIAMSOB_SCHOLAR_CATEGORY', 2);
define('TRIAMSOB_EXERCISE_CATEGORY', 5);
define('TRIAMSOB_EXAM_CATEGORY', 6);

function triamsob(){
	$p = "WHERE category=%d AND publishing_status < 2 AND publish_time < '".NOW."' ORDER BY id DESC LIMIT 5";
	$column = array('id', 'topic', 'uri');
	$admission = db_select('blog', $column, sprintf($p, TRIAMSOB_ADMISSION_CATEGORY));
	$scholar = db_select('blog', $column, sprintf($p, TRIAMSOB_SCHOLAR_CATEGORY));
	
	$p = 'WHERE category=%d ORDER BY id DESC LIMIT 5';
	$exercise = db_select_single_column('download', 'name', sprintf($p, TRIAMSOB_EXERCISE_CATEGORY));
	$old_exam = db_select_single_column('download', 'name', sprintf($p, TRIAMSOB_EXAM_CATEGORY));
	
	$clause = 'ORDER BY comment_time DESC LIMIT 5';
	$forum = db_select_single_column('forum_entry', 'topic', $clause);
	
	$render_array = array(
		'admission' => $admission,
		'scholar' => $scholar,
		'exercise' => $exercise,
		'old_exam' => $old_exam,
		'forum' => $forum,
		'category' => triamsob_get_category(),
	);
	return render($render_array, 'triamsob.tpl', 'triamsob');
}

function triamsob_get_category(){
	$clause = 'WHERE id='.TRIAMSOB_ADMISSION_CATEGORY.' OR ';
	$clause.= 'id='.TRIAMSOB_SCHOLAR_CATEGORY.' OR ';
	$clause.= 'id='.TRIAMSOB_EXERCISE_CATEGORY.' OR ';
	$clause.= 'id='.TRIAMSOB_EXAM_CATEGORY;
	return db_select_single_column('category', 'category', $clause);
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
?>
