<?php
function module_get_info_evaluation(){
	$describe = tt('Simple Evaluation for internal managment in RTNA.');
	return array(
		'name' => tt('Evaluation'),
		'description' => $describe,
	);
}

function module_init_evaluation(){
}

function module_drop_evaluation(){
}
?>
