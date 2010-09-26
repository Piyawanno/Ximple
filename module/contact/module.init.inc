<?php
function module_get_info_contact(){
	$describe = tt('Let your visitors send email to the you with out knowing your email address. ');
	$describe.= tt('Moreover, you can show them your contact information on Contact-Page.');
	return array(
		'name' => tt('Contact'),
		'description' => $describe,
	);
}

function module_init_contact(){
	include_once('Contact.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$contact = new Contact();
	$contact->initModule('contact.module.inc');
	module_add_role('contact_admin', 'Contact Administrator', 'Who can insert, edit and drop Contact.');
	module_add_cache('contact');
	module_add_panel('Contact', 'contact_admin', 'contact_write', 'create new contact');
	module_add_panel('Contact', 'contact_admin', 'contact', 'list & manage  contact');
	module_add_panel('Contact', 'contact_admin', 'contact_config', 'config contact');
	notify_add_info(tt('Contact has been successfully activated'));
	$contact_data = db_select_single_column('contact', 'name', 'WHERE section='.SECTION);
	foreach($contact_data as $key => $value){
		block_add_navigation('contact/'.$key, $value);
	}
}

function module_drop_contact(){
	include_once('Contact.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$contact = new Contact();
	$contact->dropModule();
	module_drop_role('contact_admin');
	module_drop_cache('contact');
	module_drop_panel('Contact');
	notify_add_info(tt('Contact has been successfully deactivated'));
	$navigation = cc('navigation');
	foreach($navigation as $key => $value){
		if(substr($key,0, 7) == 'contact') block_drop_navigation($key);
	}
}
?>
