<?php
function module_get_info_forum(){
	$describe = tt('Forum module for Ximple. You can use forum module for online discussion in your community.');
	return array(
		'name' => tt('Forum'),
		'description' => $describe,
	);
}

function module_init_forum(){
	include_once('Forum.class.inc');
	include_once('ForumEntry.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	
	$forum = new Forum();
	$forum->initModule('forum.module.inc');
	
	$forumEntry = new ForumEntry();
	$forumEntry->initModule('ForumEntry.class.inc');
}

function module_drop_forum(){
	include_once('Forum.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$forum = new Forum();
	$forum->dropModule();
	notify_add_info(tt('Forum has been successfully deactivated'));
	config_drop('forum_entries_number');
	flashblock_drop('forum_last_post');
	flashblock_drop('forum_last_commented');
}
?>
