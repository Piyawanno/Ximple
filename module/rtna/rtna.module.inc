<?php
execute_add_function('rtna');

function rtna(){
	document_set_path(tt('RTNA Database'), 'rtna');
	head_add_css('rtna.css');
	$data = array(
		'title' => tt('Welcome to Rtna Database'), 
	);
	$render = render($data, 'rtna.tpl', 'rtna');
	return $render;
}
?>
