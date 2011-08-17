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
	if(db_exist_table('people')){
		$clause = 'WHERE section='.SECTION;
		$event = db_select_single_column('event', 'event', $clause);
		return $event;
	}else{
		return array();
	}
}

function peopleinfo_get_people(){
	$clause = 'WHERE section='.SECTION;
	$people = db_select('people', array('id', 'uid'), $clause);
	return userinfo_get_info($people, 'uid');
}

function peopleinfo_get_people_name(){
	if(db_exist_table('people')){
		$clause = 'WHERE section='.SECTION;
		return db_select_single_column('people', 'name', $clause);
	}
	return array();
}

function peopleinfo_get_relation(){
	return array(
		0 => tt('victim'),
		1 => tt('attestor'),
		2 => tt('informant'),
		3 => tt('else'),
	);
}

function peopleinfo_get_group_warning(){
	$pattern = tt('Groups with the role of "People Information Related" should be created (<a href="%s">Group Management</a>)');
	return sprintf($pattern, SECTION_URI.Q.'group');
}

function peopleinfo_get_tagged($tag, $mode, $table, $column){
	document_set_path($tag);
	$clause = "WHERE freetag='$tag' AND mode='$mode'";
	$tagged = db_select_single_column('freetag', 'content_id', $clause, false);
	if(count($tagged)){
		$clause = 'WHERE id='.join(' OR id=', $tagged);
		$data = db_select_single_column($table, $column, $clause);
	}else{
		$data = array();
	}
	return $data;
}

function peopleinfo_get_default_datat_type(){
	return array(
		0 => tt('gender'),
		1 => tt('occupation'),
		2 => tt('age'),
	);
}
?>
