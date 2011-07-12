<?php
execute_add_function('sitemap');
execute_add_function('sitemap_update');
execute_add_function('sitemap_update_table');
execute_add_function('sitemap_config');
execute_add_function('sitemap_config_save');

function sitemap(){

}

function sitemap_update(){

}

function sitemap_update_table(){

}

function sitemap_config($params, $result){
	$result[tt('SiteMap')] = array(
		'sitemap_enable_xml' => Model::enable(tt('enable generating XML')),
		'sitemap_enable_topic' => Model::enable(tt('enable SiteMap for all topics (time consuming)')),
	);
	return $result;
}

function sitemap_config_save(){
	config_set('sitemap_enable_xml', pp('sitemap_enable_xml'));
	config_set('sitemap_enable_topic', pp('sitemap_enable_topic'));
}
?>
