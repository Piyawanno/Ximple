<?php
function module_get_info_develcard(){
	return array(
		'name' => tt('DevelCard'),
		'description' => tt('Development card for software improvments')
	);
}

function module_init_develcard(){
	include_once('DevelCard.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$develcard = new DevelCard();
	$develcard->initModule('DevelCard.class.inc');
	module_add_role('develcard_admin', 'DevelCard Administrator', 'Who can configure, edit and drop DevelCard.');
	module_add_role('develcard_moderator', 'DevelCard Moderator', 'Who can edit and drop DevelCard.');
	module_add_role('develcard_reporter', 'DevelCard Reporter', 'Who can DevelCard Report.');
	
	module_add_panel('DevelCard', 'develcard_admin', 'develcard_config', 'configure DevelCard');
	module_add_panel('DevelCard', 'develcard_admin', 'develcard', 'DevelCard report');
	module_add_panel('DevelCard', 'develcard_admin', 'develcard_list', 'list DevelCard');
	module_add_panel('DevelCard', 'develcard_admin', 'category/module/develcard', 'DevelCard category');
	module_add_panel('DevelCard', 'develcard_admin', 'develcard_write', 'submit new DevelCard');
	
	module_add_panel('DevelCard', 'develcard_moderator', 'develcard', 'DevelCard report');
	module_add_panel('DevelCard', 'develcard_moderator', 'develcard_list', 'list DevelCard');
	module_add_panel('DevelCard', 'develcard_moderator', 'develcard_write', 'submit new DevelCard');
	
	module_add_panel('DevelCard', 'develcard_reporter', 'develcard', 'DevelCard report');
	module_add_panel('DevelCard', 'develcard_reporter', 'develcard_write', 'submit new DevelCard');
}

function module_drop_develcard(){
	include_once('DevelCard.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$develcard = new DevelCard();
	$develcard->dropModule();
	module_drop_role('develcard_admin');
	module_drop_role('develcard_moderator');
	module_drop_role('develcard_reporter');	
	module_drop_panel('DevelCard');
}
?>
