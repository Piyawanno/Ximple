<?php
function peopleinfo_get_people_status(){
	return array(
		0 => tt('normal'),
		1 => tt('escape'),
		2 => tt('arrest'),
		3 => tt('sick'),
		4 => tt('lost'),
		5 => tt('dead'),
	);
}

function peopleinfo_get_event(){

}

function peopleinfo_get_people(){

}

function peopleinfo_get_relation(){
	return array(
		0 => tt('victim'),
		1 => tt('attestor'),
		2 => tt('informant'),
		3 => tt('else'),
	);
}
?>
