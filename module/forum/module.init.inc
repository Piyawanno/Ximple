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
	include_once('ForumConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once(MODULE_PATH.'flashwidget/flashwidget.module.inc');
	
	$forumEntry = new ForumEntry();
	$forumEntry->initModule('ForumEntry.class.inc');
	
	$forum = new Forum();
	$forum->initModule('Forum.class.inc');
	
	$forumConfig = new ForumConfig();
	$forumConfig->initModule('ForumConfig.class.inc');
	
	menu_drop('forum_entry');
	menu_add('forum', tt('Forum'));
	list($admin, $editor, $contributor) = content_add_role('forum_entry', tt('Forum Entry'));
	
	$panel = new PanelManager('Forum Entry');
	$panel->drop();
	
	$panel = new PanelManager('Forum');
	$panel->drop();
	$panel->appendRole($admin);
	$panel->appendRole($editor);
	$panel->appendRole($contributor);
	
	$panel->setControl($forum);
	$panel->append('forum_config', 'configure Forum');
	$panel->append('forum_manage', 'sort and manage Forum');
	$panel->submit();
	
	$panel->setControl($forumEntry);
	$panel->append('category/module/forum', 'Forum category');
	$panel->append('forum_entry_write', 'write new Forum entry');
	$panel->append('forum_entry_contributor_list', 'list my Forum entry');
	$panel->append('forum_entry_editor_list', 'list Forum entry in Section');
	$panel->submit();
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY id DESC';
	flashwidget_add('forum_entry_last_post', 'forum_entry', tt('Last posted Forum Entries'), 'forum_entry', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashwidget_add('forum_entry_last_commented', 'forum_entry', tt('Last commented Forum Entries'), 'forum_entry', 'topic', $clause);
	
	$clause = 'WHERE section='.SECTION.' AND category != 0 ORDER BY position';
	flashwidget_add('forum_list', 'forum_entry_list/forum', tt('List of Forums'), 'forum', 'name', $clause);
	
	widget_add(
		tt('Advanced Last commented Forum Entries'),
		'forum_entry_last_commented',
		'disabled',
		'forum_entry_last_commented_config',
		'forum_entry_last_commented_config_save'
	);
}

function module_drop_forum(){
	include_once('Forum.class.inc');
	include_once('ForumEntry.class.inc');
	include_once('ForumConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once(MODULE_PATH.'flashwidget/flashwidget.module.inc');
	
	$forumEntry = new ForumEntry();
	$forumEntry->dropModule();
	
	$forum = new Forum();
	$forum->dropModule();
	
	$forumConfig = new ForumConfig();
	$forumConfig->dropModule();
	
	$panel = new PanelManager('Forum');
	$panel->drop();
	
	content_drop_module('forum_entry', tt('Forum Entry'));
	menu_drop('forum');
	flashwidget_drop('forum_entry_last_post');
	flashwidget_drop('forum_entry_last_commented');
	flashwidget_drop('forum_list');
	
	widget_drop('forum_entry_last_commented');
	notify_add_info(tt('Forum has been successfully deactivated'));
}
?>
