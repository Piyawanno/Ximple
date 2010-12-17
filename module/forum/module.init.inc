<?php
function module_get_info_forum(){
	$describe = tt('Forum module for Ximple. You can use forum module for online discussion in your community.');
	return array(
		'name' => tt('Forum'),
		'description' => $describe,
	);
}

function module_init_forum(){
	include_once('ForumEntry.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$forumEntry = new ForumEntry();
	$forumEntry->initModule('forum.module.inc');
	config_set('forum_entries_number', 5);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashblock_add('forum_last_post', 'forum', tt('Last posted Forums'), 'forum', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashblock_add('forum_last_commented', 'forum', tt('Last commented Forums'), 'forum', 'topic', $clause);
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
