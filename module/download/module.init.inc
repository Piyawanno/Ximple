<?php
function module_get_info_download(){
	$describe = tt('With Download-Module, you can provide files for downloading on your website. ');
	$describe.= tt('The files are categorized with the configurations for access permission.');
	return array(
		'name' => tt('Download'),
		'description' => $describe,
	);
}

function module_init_download(){
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once('Download.class.inc');
	$download = new Download();
	$download->initModule('Download.class.inc');
	module_add_role('download_admin', 'Download Administrator', 'Who can provide new files for downloading, edit and delete them.');
	module_add_cache('download');
	module_add_panel('Download', 'download_admin', 'download_write', 'upload new file');
	module_add_panel('Download', 'download_admin', 'download', 'list & manage  download');
	module_add_panel('Download', 'download_admin', 'category/module/download', 'download category');
	notify_add_info(tt('Download has been successfully activated'));
	category_init('download');
	$dowload_dir = ROOT_PATH.'files/download/';
	if(!is_dir($dowload_dir)) mkdir($dowload_dir);
	block_add_navigation('download', tt('Download'));
}

function module_drop_download(){
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once('Download.class.inc');
	$download = new Download();
	$download->dropModule();
	module_drop_role('download_admin');
	module_drop_cache('download');
	module_drop_panel('Download');
	notify_add_info(tt('Download has been successfully deactivated'));
	block_drop_navigation('download');
}
?>
