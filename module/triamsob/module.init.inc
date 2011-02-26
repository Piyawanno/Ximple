<?php
include('triamsob.module.inc');

function module_get_info_triamsob(){
	return array(
		'name' => tt('TriamSob'),
		'description' => tt('Frontpage module and other special pages for TriamSob.Com')
	);
}

function module_init_triamsob(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	require_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	require_once('TutorSubject.class.inc');
	$tutorSubject = new TutorSubject();
	$tutorSubject->createTable();
	module_add('triamsob', 'triamsob.module.inc', 'TriamSob');
	extension_add('pre_main_render_site', 'triamsob_render_content_box');
	extension_add('additional_profile_link', 'triamsob_tutor_subject_icon');
	module_add_role('triamsob_tutor', 'Tutor', 'Who can add subject to his profile.');
}

function module_drop_triamsob(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	require_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	module_drop_role('triamsob_tutor');
	module_drop('triamsob');
	extension_drop('pre_main_render_site', 'triamsob_render_content_box');
	extension_drop('additional_profile_link', 'triamsob_tutor_subject_icon');
}
?>
