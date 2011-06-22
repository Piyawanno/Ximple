<?php
function develcard_get_status_option(){
	return array(
		0 => tt('created'),
		1 => tt('in progress'),
		2 => tt('closed'),
	);
}

function develcard_get_type_option(){
	return array(
		0 => tt('bug'),
		1 => tt('enhancement'),
		2 => tt('suggestions'),
		3 => tt('document'),
	);
}

function develcard_get_priority_option(){
	return array(
		0 => tt('0 - High'),
		1 => tt('1 - Medium'),
		2 => tt('2 - Low'),
		3 => tt('3 - No-Effect'),
	);
}
?>
