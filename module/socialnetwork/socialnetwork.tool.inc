<?php
require_once('socialnetwork.tool.inc');

function socialnetwork_get_appearance($data){
	$config = cc($data['module'].'_socialnetwork_share');
	if(is_array($config)){
		$option = socialnetwork_get_share_option();
		$appearance = array();
		foreach($option as $key => $value){
			$appearance[$key] = in_array($key, $config);
		}
		return $appearance;
	}else{
		return array();
	}
}

function socialnetwork_get_share_option(){
	return array(
		'facebook_like' => 'Facebook Like',
		'facebook_share' => 'Facebook Share',
		'twitter' => 'Tweet Button',
		'email' => 'email to friends'
	);
}

function socialnetwork_get_block_array(){
	return array(
		'socialnetwork_facebook_like_box' => 'Facebook Like Box',
		'socialnetwork_facebook_activity_feed' => 'Facebook Activity Feed',
		'socialnetwork_facebook_live_stream' => 'Facebook Live Stream',
		'socialnetwork_twitter_profile' => 'Twitter Profile',
		'socialnetwork_twitter_faves' => 'Twitter Faves',
	);
}
?>
