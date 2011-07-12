<?php
function module_get_info_sitemap(){
	$describe = tt('With this module, Site Map will be automatically generated based on contents in Section.');
	return array(
		'name' => tt('SiteMap'),
		'description' => $describe,
		'require' => array('directory'),
	);
}

function module_init_sitemap(){
	module_add('sitemap', 'sitemap.module.inc', 'Site Map');
	
	extension_add('module_activate', 'sitemap_update_table');
	extension_add('module_deactivate', 'sitemap_update_table');
	extension_add('content_insert', 'sitemap_update');
	extension_add('content_update', 'sitemap_update');
	extension_add('content_drop', 'sitemap_update');
	extension_add('section_config', 'sitemap_config');
	extension_add('section_config_save', 'sitemap_config_save');
	
	config_set('sitemap_enable_xml', true);
	config_set('sitemap_enable_topic', false);
}

function module_drop_sitemap(){
	module_drop('sitemap');
	
	extension_drop('module_activate', 'sitemap_update_table');
	extension_drop('module_deactivate', 'sitemap_update_table');
	extension_drop('content_insert', 'sitemap_update');
	extension_drop('content_update', 'sitemap_update');
	extension_drop('content_drop', 'sitemap_update');
	extension_drop('section_config', 'sitemap_config');
	extension_drop('section_config_save', 'sitemap_config_save');
}
?>
