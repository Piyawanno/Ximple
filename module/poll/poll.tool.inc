<?php
function poll_permission_option(){
	return array(
		0 => tt('everyone can vote'),
		1 => tt('only authenticated user can vote'),
		2 => tt('only user with Poll-Voter roll can vote'),
	);
}
?>
