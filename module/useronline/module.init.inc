<?php
function module_get_info_useronline(){
	return array(
		'name' => tt('UserOnline'),
		'description' => tt('Show user status, who is now online.')
	);
}

function module_init_useronline(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	module_add('useronline', 'useronline.module.inc', 'UserOnline');
	block_add(tt('Who is online (count)'), 'useronline_block_cont');
	block_add(tt('Who is online (list)'), 'useronline_block_user_list');
	extension_add('main_init', 'useronline_set_access');
}

function module_drop_useronline(){
	require_once(ROOT_PATH.'include/tool/block.tool.inc');
	module_drop('useronline');
	block_drop('useronline_block_count');
	block_drop('useronline_block_user_list');
	extension_drop('main_init', 'useronline_set_access');
}
?>
