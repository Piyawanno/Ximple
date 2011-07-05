<?php
function module_get_info_meeting(){
	$describe = tt('Meeting appointment between member in Section.');
	return array(
		'name' => tt('Meeting'),
		'description' => $describe,
	);
}

function module_init_meeting(){
	include_once('Meeting.class.inc');
	include_once('MeetingConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once(MODULE_PATH.'flashwidget/FlashWidgetManager.class.inc');
	
	$meeting = new Meeting();
	$meeting->initModule('Meeting.class.inc');
	
	$meetingConfig = new MeetingConfig();
	$meetingConfig->initModule('MeetingConfig.class.inc');
	
	config_set('meeting_entries_number', 5);
	
	$flash = new FlashWidgetManager('meeting_last_post');
	$flash->setMode('meeting');
	$flash->setName(tt('Last posted Meetings'));
	$flash->setTable('meeting');
	$flash->setColumn('topic');
	$flash->setClause('WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC');
	$flash->submit();
	
	$flash = new FlashWidgetManager('meeting_last_commented');
	$flash->setMode('meeting');
	$flash->setName(tt('Last commented Meetings'));
	$flash->setTable('meeting');
	$flash->setColumn('topic');
	$flash->setClause('WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC');
	$flash->submit();
}

function module_drop_meeting(){
	include_once('Meeting.class.inc');
	include_once('MeetingConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once(MODULE_PATH.'flashwidget/FlashWidgetManager.class.inc');
	
	$meeting = new Meeting();
	$meeting->dropModule();
	
	$meetingConfig = new MeetingConfig();
	$meetingConfig->dropModule();
	
	$flash = new FlashWidgetManager('meeting_last_post');
	$flash->drop();
	
	$flash = new FlashWidgetManager('meeting_last_commented');
	$flash->drop();
	
	
	notify_add_info(tt('Meeting has been successfully deactivated'));
	config_drop('meeting_entries_number');
}
?>
