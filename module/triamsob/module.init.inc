<?php
function module_get_info_triamsob(){
	return array(
		'name' => tt('TriamSob'),
		'description' => tt('Frontpage module and other special pages for TriamSob.Com')
	);
}

function module_init_triamsob(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	module_add('triamsob', 'triamsob.module.inc', 'TriamSob');
	extension_add('pre_main_render_site', 'triamsob_render_content_box');
	
	$clause = 'WHERE (publishing_status < 2 AND category='.TRIAMSOB_TUTOR_CATEGORY.') ';
	$clause.= 'ORDER BY publish_time DESC';
	flashblock_add('tutor_article', 'journal', tt('Tutor Article'), 'journal', 'topic', $clause);
	
	$clause = 'WHERE (publishing_status < 2 AND category='.TRIAMSOB_STUDENT_CATEGORY.') ';
	$clause.= 'ORDER BY publish_time DESC';
	flashblock_add('student_article', 'journal', tt('Student Article'), 'journal', 'topic', $clause);
	
}

function module_drop_triamsob(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	module_drop('triamsob');
	extension_drop('pre_main_render_site', 'triamsob_render_content_box');
	flashblock_drop('tutor_article');
	flashblock_drop('student_article');
}
?>
