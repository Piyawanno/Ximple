<?php
function module_get_info_tutorialschool(){
	$describe = tt('Article about TutorialSchool for TriamSob.com.');
	return array(
		'name' => tt('TutorialSchool'),
		'description' => $describe,
	);
}

function module_init_tutorialschool(){
	include_once('TutorialSchool.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$tutorialschool = new TutorialSchool();
	$tutorialschool->initModule('tutorialschool.module.inc');
	config_set('tutorialschool_entries_number', 5);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashblock_add('tutorialschool_last_post', 'tutorialschool', tt('Last posted TutorialSchools'), 'tutorialschool', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashblock_add('tutorialschool_last_commented', 'tutorialschool', tt('Last commented TutorialSchools'), 'tutorialschool', 'topic', $clause);
}

function module_drop_tutorialschool(){
	include_once('TutorialSchool.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$tutorialschool = new TutorialSchool();
	$tutorialschool->dropModule();
	notify_add_info(tt('TutorialSchool has been successfully deactivated'));
	config_drop('tutorialschool_entries_number');
	flashblock_drop('tutorialschool_last_post');
	flashblock_drop('tutorialschool_last_commented');
}
?>
