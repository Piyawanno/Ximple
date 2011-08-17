<?php
function evaluation_status_option(){
	return array(
		0 => tt('in progress'),
		1 => tt('finish'),
	);
}

function evaluation_result_option(){
	return array(
		0 => tt('poor'),
		1 => tt('failed'),
		2 => tt('satisfied'),
		3 => tt('good'),
		4 => tt('very good'),
	);
}
?>
