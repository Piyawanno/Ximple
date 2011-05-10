<?php
function module_get_info_video(){
	$describe = tt('With Video Module, you can provide video streaming on your website. ');
	$describe.= tt('Be careful with the bandwidth. Vedio streaming is very bandwidth hungry.');
	return array(
		'name' => tt('Video'),
		'description' => $describe,
	);
}

function module_init_video(){
	include_once('Video.class.inc');
	include_once('VideoConfig.class.inc');
	
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	
	$video = new Video();
	$video->initModule('Video.class.inc');
	$videoConfig = new VideoConfig();
	$videoConfig->initModule('VideoConfig.class.inc');
	
	config_set('video_entries_number', 5);
	config_set('video_width', 480);
	config_set('video_height', 390);
	$video_directoy = ROOT_PATH.'files/video';
	if(!is_dir($video_directoy)) mkdir($video_directoy);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashblock_add('video_last_post', 'video', tt('Last posted Videos'), 'video', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashblock_add('video_last_commented', 'video', tt('Last commented Videos'), 'video', 'topic', $clause);
}

function module_drop_video(){
	include_once('Video.class.inc');
	include_once('VideoConfig.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	
	$video = new Video();
	$video->dropModule();
	$videoConfig = new VideoConfig();
	$videoConfig->dropModule();
	
	notify_add_info(tt('Video has been successfully deactivated'));
	config_drop('video_entries_number');
	config_drop('video_width');
	config_drop('video_width');
	flashblock_drop('video_last_post');
	flashblock_drop('video_last_commented');
}
?>
