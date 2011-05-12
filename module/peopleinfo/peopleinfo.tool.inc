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
	$clause = 'WHERE section='.SECTION;
	$event = db_select_single_column('event', 'event', $clause);
	return $event;
}

function peopleinfo_get_people(){
	$clause = 'WHERE section='.SECTION;
	$people = db_select('people', array('id', 'people'), $clause);
	return userinfo_get_info($people, 'people');
}

function peopleinfo_get_unprocessed_user(){
	$people = userinfo_get_login_name_by_role('peopleinfo_related');
	$people_info = peopleinfo_get_people();
	$processed_people = array();
	foreach($people_info as $key => $value){
		$processed_people[] = $value['people']['id'];
	}
	foreach($people as $key => $value){
		if(in_array($key, $processed_people)) unset($people[$key]);
	}
	return $people;
}

function peopleinfo_get_people_name(){
	$people_name = array();
	$people = peopleinfo_get_people();
	foreach($people as $key => $value){
		$people_name[$value['id']] = $value['people']['login_name'];
	}
	return $people_name;
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
