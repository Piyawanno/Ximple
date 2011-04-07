<?php
function preconfig_init(){
	include(ROOT_PATH.'include/tool/main.tool.inc');
	include(ROOT_PATH.'include/tool/extension.tool.inc');
	include(ROOT_PATH.'include/tool/execute.tool.inc');
	include(ROOT_PATH.'include/tool/translate.tool.inc');
	include(ROOT_PATH.'include/tool/notify.tool.inc');
	include(ROOT_PATH.'include/tool/document.tool.inc');
	include(ROOT_PATH.'include/tool/count.tool.inc');
	include(ROOT_PATH.'include/tool/block.tool.inc');
	include(ROOT_PATH.'module/module/module.module.inc');
	define('MODE_PAGE', 0);
}
	
function preconfig_blog(){
	preconfig_init();
	module_prepare();
	include(ROOT_PATH.'module/blog/module.init.inc');
	module_init_blog();
	config_set('index_mode', 'blog');
	config_append('feed_mode', 'blog');
	config_save();
	module_post();
}

function preconfig_personal(){
}

function preconfig_community(){
}

function preconfig_document(){
}

function preconfig_SME(){
}

?>
