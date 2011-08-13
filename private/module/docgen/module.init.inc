<?php
function module_get_info_docgen(){
	$describe = tt('Document generation for Royal Thai Navy Academy.');
	return array(
		'name' => tt('DocGen'),
		'description' => $describe,
	);
}

function module_init_docgen(){
	include_once('DocGen.class.inc');
	$docgen = new DocGen();
	$docgen->initModule('DocGen.class.inc');
	module_add_role('docgen_admin', 'DocGen Administrator', 'Who can create, edit and delete all generated documents.');
	module_add_role('docgen_contributor', 'DocGen Contributor', 'Who can create document, edit and delete own documents.');
	
	module_add_panel('DocGen', 'docgen_admin', 'docgen_write', 'generate new document');
	module_add_panel('DocGen', 'docgen_admin', 'docgen_admin_list', 'list document in Section');
	module_add_panel('DocGen', 'docgen_admin', 'docgen_contributor_list', 'list my document');
	
	module_add_panel('DocGen', 'docgen_contributor', 'docgen_write', 'generate new document');
	module_add_panel('DocGen', 'docgen_contributor', 'docgen_contributor_list', 'list my document');
	
	notify_add_info(tt('DocGen has been successfully activated'));
	
	module_add_cache('docgen');
	$dowload_dir = FILES_PATH.'docgen/';
	if(!is_dir($dowload_dir)) mkdir($dowload_dir);
}

function module_drop_docgen(){
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once('DocGen.class.inc');
	$docgen = new DocGen();
	$docgen->dropModule();
	module_drop_role('docgen_admin');
	module_drop_cache('docgen');
	module_drop_panel('DocGen');
	notify_add_info(tt('DocGen has been successfully deactivated'));
}
?>
