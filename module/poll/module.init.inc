<?php
function module_get_info_poll(){
	$description = tt('Poll module for XimpleCMS. It can be use as a widget or can be embed in other module.');
	return array(
		'name' => tt('Poll'),
		'description' => $description,
	);
}

function module_init_poll(){
	require('Poll.class.inc');
	require('PollCoiseModel.class.inc');
	require('PollVoteModel.class.inc');
	include_once(INCLUDE_PATH.'class/QuickTableCreator.class.inc');
	
	$poll = new Poll();
	$poll->initModule('Poll.class.inc');
	
	$pollChoise = new QuickTableCreator(new PollChoiseModel());
	$pollChoise->create();
	
	$pollVote = new QuickTableCreator(new PollVoteModel());
	$pollVote->create();
	
	$admin = new RoleManager('poll_admin');
	$admin->setName('Poll Administrator');
	$admin->setDescription('Who can insert, edit and drop Poll.');
	$admin->submit();
	
	$panel = new PanelManager('Poll');
	$panel->setControl($poll);
	$panel->append('poll_write', 'create new Poll');
	$panel->append('poll_list', 'list & manage  Poll');
	$panel->appendRole($admin);
	$panel->submit();
	
	$widget = new WidgetManager(tt('Poll'), 'poll_widget');
	$widget->submit();
	
	extension_add('content_post_select', 'poll_embed');
}

function module_drop_poll(){
	require('Poll.class.inc');
	
	$poll = new Poll();
	$poll->dropModule();
	
	$admin = new RoleManager('poll_admin');
	$admin->drop();
	
	$panel = new PanelManager('Poll');
	$panel->drop();
	
	$widget = new WidgetManager(tt('Poll'), 'poll_widget');
	$widget->drop();
	
	extension_drop('content_post_select', 'poll_embed');
}
?>
