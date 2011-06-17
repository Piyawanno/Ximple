<?php
function module_get_info_directory(){
	$description = tt('Directory is a tree-structured content management system and major module of Ximple. ');
	$description.= tt('A Directory can contain many Sub-Directories and Pages. ');
	$description.= tt('It is powerful, flexible and fully extensible.');
	return array(
		'name' => tt('Directory'),
		'description' => $description,
	);
}

function module_init_directory(){
	include_once('PageDirectory.class.inc');
	include_once('DirectoryConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/menu.tool.inc');
	
	$directory = new PageDirectory();
	$directory->initModule();
	$directoryConfig = new DirectoryConfig();
	$directoryConfig->initModule('DirectoryConfig.class.inc');
	
	$directory_name = FILES_PATH.'directory';
	if(!is_dir($directory_name)) mkdir($directory_name);
	
	module_drop_panel(tt('Page'));
	menu_drop('page');
	menu_add('directory', tt('Main Page'));
	module_add_role('directory_admin', 'Directory Administrator', 'Who can create, edit and drop all Directories.');
	module_add_role('directory_contributor', 'Directory Contributor', 'Who can create Sub-Directories in allowed Directories.');
	
	module_add_panel('Directory', 'directory_contributor', 'directory_list', 'list my Directory');
	module_add_panel('Directory', 'directory_admin', 'directory_editor_list', 'list Directory in section');
	module_add_panel('Directory', 'page_admin', 'category/module/page', 'Page category');
	module_add_panel('Directory', 'page_contributor', 'page_contributor_list', 'list my Page');
	module_add_panel('Directory', 'page_editor', 'page_editor_list', 'list Page in section');
	
	module_add_cache('directory');
	notify_add_info(tt('Directory has been successfully activated'));
}

function module_drop_directory(){
	include_once('PageDirectory.class.inc');
	include_once('DirectoryConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/menu.tool.inc');
	
	$directory = new PageDirectory();
	$directory->dropModule();
	
	$directoryConfig = new DirectoryConfig();
	$directoryConfig->dropModule();
	
	menu_drop('directory');
	module_drop('page');
	module_drop_role('directory_admin');
	module_drop_cache('directory');
	module_drop_panel('Directory');
	notify_add_info(tt('Directory has been successfully deactivated'));
}
?>
