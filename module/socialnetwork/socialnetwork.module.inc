<?php
require_once('socialnetwork.tool.inc');

execute_add_function('socialnetwork_share');
execute_add_function('socialnetwork_share_config');

execute_add_function('socialnetwork_facebook_like_box');
execute_add_function('socialnetwork_facebook_like_box_config');
execute_add_function('socialnetwork_facebook_like_box_save');

execute_add_function('socialnetwork_facebook_activity_feed');
execute_add_function('socialnetwork_facebook_activity_feed_config');
execute_add_function('socialnetwork_facebook_activity_feed_save');

execute_add_function('socialnetwork_facebook_live_stream');
execute_add_function('socialnetwork_facebook_live_stream_config');
execute_add_function('socialnetwork_facebook_live_stream_save');

execute_add_function('socialnetwork_twitter_profile');
execute_add_function('socialnetwork_twitter_profile_config');
execute_add_function('socialnetwork_twitter_profile_save');

execute_add_function('socialnetwork_twitter_faves');
execute_add_function('socialnetwork_twitter_faves_config');
execute_add_function('socialnetwork_twitter_faves_save');

function socialnetwork_share($data){
	foreach($data as $key => $value){
		$render_array['data'] = $value;
		if(!isset($render_array['appearance'])){
			$render_array['appearance'] = socialnetwork_get_appearance($value);
		}
		$data[$key]['content'] = render($render_array, 'socialnetwork_share.tpl', 'socialnetwork_share');
	}
	return $data;
}

function socialnetwork_share_config($config){
	$label = tt('share by SocialNetwork');
	$option = socialnetwork_get_share_option();
	$config[$label]['socialnetwork_share'] = Model::checkbox('', $option);
	return $config;
}

function socialnetwork_facebook_like_box(){
}

function socialnetwork_facebook_like_box_config(){
}

function socialnetwork_facebook_like_box_save(){
}

function socialnetwork_facebook_activity_feed(){
}

function socialnetwork_facebook_activity_feed_config(){
}

function socialnetwork_facebook_activity_feed_save(){
}

function socialnetwork_facebook_live_stream(){
}

function socialnetwork_facebook_live_stream_config(){
}

function socialnetwork_facebook_live_stream_save(){
}

function socialnetwork_twitter_profile(){
}

function socialnetwork_twitter_profile_config(){
}

function socialnetwork_twitter_profile_save(){
}

function socialnetwork_twitter_faves(){
}

function socialnetwork_twitter_faves_config(){
}

function socialnetwork_twitter_faves_save(){
}
?>
