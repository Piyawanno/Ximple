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
	
	$poll = new Poll();
	$poll->initModule('Poll.class.inc');
}

function module_drop_poll(){
	require('Poll.class.inc');
	
	$poll = new Poll();
	$poll->dropModule();
}
?>
