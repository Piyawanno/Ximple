<?php
function module_get_info_socialnetwork(){
	$describe = tt('With SocialNetwork, you can simply share your contents per many social networks.');
	return array(
		'name' => tt('SocialNetwork'),
		'description' => $describe,
	);
}

function module_init_socialnetwork(){
}

function module_drop_socialnetwork(){
}
?>
