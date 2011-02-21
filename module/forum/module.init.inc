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
	
	$forumEntry = new ForumEntry();
	$forumEntry->initModule('ForumEntry.class.inc');
	
	$forum = new Forum();
	$forum->initModule('forum.module.inc');
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY id DESC';
	flashblock_add('forum_entry_last_post', 'forum_entry', tt('Last posted Forum Entries'), 'forum_entry', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashblock_add('forum_entry_last_commented', 'forum_entry', tt('Last commented Forum Entries'), 'forum_entry', 'topic', $clause);
	
	$clause = 'WHERE section='.SECTION.' AND category != 0 ORDER BY position';
	flashblock_add('forum_list', 'forum', tt('List of Forums'), 'forum', 'name', $clause);
	
	block_add(tt('Advanced Last commented Forum Entries'), 'forum_entry_last_commented');
}

function module_drop_forum(){
	include_once('Forum.class.inc');
	include_once('ForumEntry.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	
	$forumEntry = new ForumEntry();
	$forumEntry->dropModule();
	
	$forum = new Forum();
	$forum->dropModule();
	notify_add_info(tt('Forum has been successfully deactivated'));
	module_drop_panel('Forum');
	menu_drop('forum');
	flashblock_drop('forum_entry_last_post');
	flashblock_drop('forum_entry_last_commented');
	flashblock_drop('forum_list');
	block_drop('forum_entry_last_commented');
}
?>
