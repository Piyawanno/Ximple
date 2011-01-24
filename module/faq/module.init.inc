<?php
function module_get_info_faq(){
	return array(
		'name' => tt('FAQ'),
		'description' => tt('Frequency Asked Question. An introduction to Ximple can be discover here.')
	);
}

function module_init_faq(){
	include_once('FAQ.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$faq = new FAQ();
	$faq->initModule('FAQ.class.inc');
	module_add_role('faq_admin', 'FAQ Administrator', 'Who can configure, edit and drop Faq');
	module_add_role('faq_moderator', 'FAQ Moderator', 'Who can edit and drop faq.');
	
	module_add_panel('FAQ', 'faq_admin', 'category/module/faq', 'FAQ category');
	module_add_panel('FAQ', 'faq_admin', 'faq_arrange', 'organize FAQ page ');
	module_add_panel('FAQ', 'faq_admin', 'faq_list', 'list all questions');
	module_add_panel('FAQ', 'faq_admin', 'faq_write', 'write new question');

	module_add_panel('FAQ', 'faq_moderator', 'faq_list', 'list all questions');
	module_add_panel('FAQ', 'faq_moderator', 'faq_write', 'write new question');
	
	block_add_navigation('faq', tt('FAQ'));
	
	notify_add_info(tt('FAQ has been successfully activated'));
}

function module_drop_faq(){
	include_once('FAQ.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$faq = new FAQ();
	$faq->dropModule();
	module_drop_role('faq_admin');
	module_drop_role('faq_moderator');
	module_drop_panel('FAQ');
	block_drop_navigation('faq');
	notify_add_info(tt('FAQ has been successfully deactivated'));
}
?>
