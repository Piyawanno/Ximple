<?php
require_once('socialnetwork.tool.inc');

function socialnetwork_like_type_config(){
	$option = array(
		'disable' => tt('disable'),
		'standard' => tt('standard'),
		'button_count' => tt('button count'),
		'box_count' => tt('box count')
	);
	return Model::select(tt('type'), $option);
}

function socialnetwork_width_config($data=null){
	$model = Model::char(tt('width'));
	$model->data = $data;
	return $model;
}

function socialnetwork_height_config($data=null){
	$model = Model::char(tt('height'));
	$model->data = $data;
	return $model;
}

function socialnetwork_color_config($data=null){
	$option = array(
		'light' => tt('light'),
		'dark' => tt('dark'),
	);
	$model = Model::select(tt('color scheme'), $option);
	$model->data = $data;
	return $model;
}

function socialnetwork_tweet_type_config(){
	$option = array(
		'disable' => tt('disable'),
		'none' => tt('no count'),
		'horizontal' => tt('horizontal count'),
		'vertical' => tt('vertical count')
	);
	return Model::select(tt('type'), $option);
}

function socialnetwork_uri_config($label, $data=null){
	$model = Model::char($label);
	$model->data = $data;
	return $model;
}

function socialnetwork_like_box_appearance_config(){
	$option = array(
		'faces' => tt('Faces'),
		'stream' => tt('Stream'),
		'header' => tt('Header'),
	);
	$model = Model::checkbox(tt('appearance'), $option);
	$model->data = cc('socialnetwork_like_box_appearance');
	return $model;
}

function socialnetwork_activity_feed_appearance_config(){
	$option = array(
		'recommendations' => tt('Recomendations'),
		'header' => tt('Header'),
	);
	$model = Model::checkbox(tt('appearance'), $option);
	$model->data = cc('socialnetwork_activity_feed_appearance');
	return $model;
}

function socialnetwork_profile_appearance_config(){
	$model = socialnetwork_twitter_appearance_config();
	$model->data = cc('socialnetwork_profile_appearance');
	return $model;
}

function socialnetwork_faves_appearance_config(){
	$model = socialnetwork_twitter_appearance_config();
	$model->data = cc('socialnetwork_faves_appearance');
	return $model;
}

function socialnetwork_twitter_appearance_config(){
	$option = array(
		'scrollbar' => tt('scrollbar'),
		'loop' => tt('loop'),
		'live' => tt('live'),
		'hashtags' => tt('hashtags'),
		'timestamp' => tt('timestamp'),
		'avatars' => tt('avatars'),
	);
	return Model::checkbox(tt('appearance'), $option);
}

function socialnetwork_get_block_array(){
	return array(
		'socialnetwork_like_box' => 'Facebook Like Box',
		'socialnetwork_activity_feed' => 'Facebook Activity Feed',
		'socialnetwork_profile' => 'Twitter Profile',
		'socialnetwork_faves' => 'Twitter Faves',
	);
}
?>
