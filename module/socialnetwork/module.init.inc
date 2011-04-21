<?php
function module_get_info_socialnetwork(){
	$describe = tt('With SocialNetwork, you can simply share your contents per many social networks.');
	return array(
		'name' => 'SocialNetwork',
		'description' => $describe,
	);
}

function module_init_socialnetwork(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	require_once('socialnetwork.tool.inc');
	module_add('socialnetwork', 'socialnetwork.module.inc', 'SocialNetwork');
	$blocks = socialnetwork_get_block_array();
	foreach($blocks as $key => $value){
		block_add($value, $key, 'disabled', $key.'_config', 'socialnetwork_save_config');
	}
	extension_add('content_post_select', 'socialnetwork_share');
	extension_add('content_config', 'socialnetwork_share_config');
}

function module_drop_socialnetwork(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	require_once('socialnetwork.tool.inc');
	module_drop('socialnetwork');
	$blocks = socialnetwork_get_block_array();
	foreach($blocks as $key => $value){
		block_drop($key);
	}
	extension_drop('content_post_select', 'socialnetwork_share');
	extension_drop('content_config', 'socialnetwork_share_config');
}
?>
