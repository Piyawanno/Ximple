<?php
function module_get_info_wrest(){
	$describe = tt('Module for homepage of Women Network Reshaping Thailand (WREST).');
	return array(
		'name' => tt('WREST'),
		'description' => $describe,
	);
}

function module_init_wrest(){
	module_add('wrest', 'wrest.module.inc', 'WREST');
	
	extension_add('section_config', 'wrest_config');
	extension_add('section_config_save', 'wrest_config_save');
	
	config_set('wrest_news_category', 1);
	config_set('wrest_news_number', 5);
	config_set('wrest_article_category', 1);
	config_set('wrest_article_number', 5);
	config_set('wrest_meeting_number', 5);
	config_set('wrest_forum_number', 5);
	config_set('wrest_word_count', 5);
}

function module_drop_wrest(){
	module_drop('wrest');
	
	extension_drop('section_config', 'wrest_config');
	extension_drop('section_config_save', 'wrest_config_save');
}
?>
