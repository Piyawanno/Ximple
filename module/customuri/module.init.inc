<?php
function module_get_info_customuri(){
	$describe = tt('Customize URI of each page to improve SEO (Search Engine Optimization).');
	return array(
		'name' => tt('Custom URI'),
		'description' => $describe,
	);
}

function module_init_customuri(){
	if(cc('friendly_url_enable')){
		include_once('CustomURI.class.inc');
		$customuri = new CustomURI();
		$customuri->initModule('customuri.module.inc');
		module_add_role('customuri_admin', 'CustomURI Administrator', 'Who can add edit and drop Custom URI.');
		module_add_panel('Custom URI', 'customuri_admin', 'customuri', 'manage Custom URI');
		module_add_panel('Custom URI', 'customuri_admin', 'customuri_write', 'add new Custom URI');
		extension_add('main_init', 'customuri_map');
		extension_add('post_main_render', 'customuri_post_render');
	}else{
		notify_add_error(tt('Custom URI cannot be enabled without enabling "friendly URI".'));
	}
}

function module_drop_customuri(){
	include_once('CustomURI.class.inc');
	$customuri = new CustomURI();
	$customuri->dropModule();
	module_drop_role('customuri_admin');
	module_drop_panel('Custom URI');
}
?>
