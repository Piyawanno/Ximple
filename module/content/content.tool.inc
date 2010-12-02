<?php
include_once(ROOT_PATH.'include/tool/menu.tool.inc');

function content_init_module($moduleName, $moduleTitle){
	include_once(ROOT_PATH.'module/category/category.tool.inc');
	$adminGroup = $moduleName.'_admin';
	$editorGroup = $moduleName.'_editor';
	$contributorGroup = $moduleName.'_contributor';
	
	$categoryMode = 'category/module/'.$moduleName;
	$writeMode = $moduleName.'_write';
	$editorListMode = $moduleName.'_editor_list';
	$contributorListMode = $moduleName.'_contributor_list';
	$configMode = $moduleName.'_config';
	
	category_init($moduleName);
	module_add_feed($moduleName, $moduleTitle);
	module_add_cache($moduleName);
	
	$adminDescription = sprintf('Who can configure, insert, edit and drop %s from everyone.', $moduleTitle);
	$editorDescription = sprintf('Who can insert, edit and drop %s from everyone.', $moduleTitle);
	$contributorDescription = sprintf('Who can insert, edit and drop own %s.', $moduleTitle);
	
	module_add_role($adminGroup, $moduleTitle.' Administrator', $adminDescription);
	module_add_role($editorGroup, $moduleTitle.' Editor', $editorDescription);
	module_add_role($contributorGroup, $moduleTitle.' Contributor', $contributorDescription);
	
	module_add_panel($moduleTitle, $adminGroup, $categoryMode, $moduleTitle.' category');
	module_add_panel($moduleTitle, $adminGroup, $writeMode, 'write new '.$moduleTitle.' entry');
	module_add_panel($moduleTitle, $adminGroup, $contributorListMode, 'list my '.$moduleTitle);
	module_add_panel($moduleTitle, $adminGroup, $editorListMode, 'list '.$moduleTitle.' in Section');
	module_add_panel($moduleTitle, $adminGroup, $configMode, 'configure '.$moduleTitle);
	
	module_add_panel($moduleTitle, $editorGroup, $writeMode, 'write new '.$moduleTitle.' entry');
	module_add_panel($moduleTitle, $editorGroup, $contributorListMode, 'list my '.$moduleTitle);
	module_add_panel($moduleTitle, $editorGroup, $editorListMode, 'list '.$moduleTitle.' in Section');
	
	module_add_panel($moduleTitle, $contributorGroup, $writeMode, 'write new '.$moduleTitle.' entry');
	module_add_panel($moduleTitle, $contributorGroup, $contributorListMode, 'list my '.$moduleTitle);
	
	config_set($moduleName.'_comment_permission', array(0, 1, 2, 3));
	config_set($moduleName.'_comment_permission_default', 0);
	config_set($moduleName.'_appearance', array());
	
	config_set($moduleName.'_publishing_status', array(2, 3));
	config_set($moduleName.'_publishing_status_default', 3);
	
	config_set($moduleName.'_comment_write_label', tt('Please, write your opinion.'));
	config_set($moduleName.'_comment_page_length', 10);
	config_set($moduleName.'_comment_show_avatar', false);
	
	menu_add($moduleName, $moduleTitle);
}

function content_drop_module($moduleName, $moduleTitle){
	$adminGroup = $moduleName.'_admin';
	$editorGroup = $moduleName.'_editor';
	$contributorGroup = $moduleName.'_contributor';
	
	module_drop_feed($moduleName);
	module_drop_cache($moduleName);
	module_drop_role($adminGroup);
	module_drop_role($editorGroup);
	module_drop_role($contributorGroup);
	module_drop_panel($moduleTitle);
	
	config_drop($moduleName.'_comment_permission');
	config_drop($moduleName.'_comment_permission_default');
	config_drop($moduleName.'_publishing_status');
	config_drop($moduleName.'_publishing_status_default');
	
	config_drop($moduleName.'_comment_write_label');
	config_drop($moduleName.'_comment_page_length');
	config_drop($moduleName.'_comment_show_avatar');
	
	menu_drop($moduleName);
}

function content_get_comment_permission(){
	return array(
		0 => tt('everybody can comment'),
		1 => tt('only authenticated user can comment'),
		2 => tt('read only'),
		3 => tt('disable'),
	);
}

function content_get_publishing_status(){
	return array(
		0 => tt('published'),
		1 => tt('featured'),
		2 => tt('in review'),
		3 => tt('draft'),
	);
}
?>
