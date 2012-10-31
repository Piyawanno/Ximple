<?php
function rtna_get_cadet_uid_option(){
	if(db_exist_table('rtna_yearserie')){
		$all_cadet = userinfo_get_login_name_by_role('rtna_cadet');
		$clause = 'WHERE section='.SECTION;
		$exist_uid = db_select_single_column('rtna_cadet', 'uid', $clause);
		foreach($exist_uid as $key => $value){
			unset($all_cadet[$value]);
		}
		return $all_cadet;
	}else{
		return array();
	}
}

function rtna_get_Officer_uid_option(){
	if(db_exist_table('rtna_yearserie')){
		$all_officer = userinfo_get_login_name_by_role('rtna_officer');
		$clause = 'WHERE section='.SECTION;
		$exist_uid = db_select_single_column('rtna_officer', 'uid', $clause);
		foreach($exist_uid as $key => $value){
			unset($all_officer[$value]);
		}
		return $all_officer;
	}else{
		return array();
	}
}

function rtna_get_yearserie_option(){
	if(db_exist_table('rtna_yearserie')){
		return db_select_single_column('rtna_yearserie', 'serie_number');
	}else{
		return array();
	}
}

function rtna_get_faculty_option(){
	if(db_exist_table('rtna_faculty')){
		return db_select_single_column('rtna_faculty', 'name');
	}else{
		return array();
	}
}

function rtna_get_club_option(){
	if(db_exist_table('rtna_club')){
		return db_select_single_column('rtna_club', 'name');
	}else{
		return array();
	}
}

function rtna_get_rtna_officer_option(){
	if(db_exist_table('rtna_officer')){
		return db_select_single_column('rtna_officer', 'name');
	}else{
		return array();
	}
}

function rtna_get_rtna_cadet_option(){
	if(db_exist_table('rtna_cadet')){
		$clause = 'WHERE section='.SECTION;
		$cadet =  db_select('rtna_cadet', array('name', 'surname'), $clause);
		$result = array();
		foreach($cadet as $key => $value){
			$result[$key] = $value['name'].' '.$value['surname'];
		}
		return $result;
	}else{
		return array();
	}
}

function rtna_get_Activity_option(){
	if(db_exist_table('rtna_Activity')){
		return db_select_single_column('rtna_Activity', 'name');
	}else{
		return array();
	}
}

function rtna_get_Health_option(){
	if(db_exist_table('rtna_health')){
		return db_select_single_column('rtna_health', 'cadet');
	}else{
		return array();
	}
}

function rtna_get_cadet_party_option(){
	return array(
		0 => tt('undefined'),
		1 => tt('naval'),
		2 => tt('mechanical'),
		3 => tt('marine'),
	);
}

function rtna_get_cadet_rank_option(){
	return array(
		0 => tt('NC.'),
	);
}
function rtna_get_officer_rank_option(){
	return array(
		0 => tt('SubLt.'), 
		1 => tt('Lt.JG.'),
		2 => tt('Lt.'),
		3 => tt('LCdr.'),
		4 => tt('Cdr.'),
		5 => tt('Capt.'),
		6 => tt('SrCapt.'),
		7 => tt('RAdm.'),
		8 => tt('VAdm.'),
		9 => tt('Adm.'),
	);
}

function rtna_get_parent_option(){
	if(db_exist_table('rtna_belong')){
		return db_select_single_column('rtna_belong', 'name','WHERE is_leaf=0');
	}else{
		return array();
    }
}

function enable($parent){
		include_once('column/CheckSlideColumn.class.inc');
		$option = array(1 => '');
		$modelColumn = new CheckSlideColumn($parent, $option);
		$modelColumn->setType('int');
		return $modelColumn;
	}

function rtna_get_building_option(){
	if(db_exist_table('rtna_building')){
		return db_select_single_column('rtna_building', 'name');
	}else{
		return array();
	}
}

function rtna_get_facuty_option(){
	if(db_exist_table('rtna_facuty')){
		return db_select_single_column('rtna_facuty', 'name');
	}else{
		return array();
	}
}

function rtna_get_lectureClass_option(){
	if(db_exist_table('rtna_lectureClass')){
		return db_select_single_column('rtna_lectureClass', 'lecture_class');
	}else{
		return array();
	}
}

function rtna_get_educationYear_option(){
	if(db_exist_table('rtna_educationYear')){
		return db_select_single_column('rtna_educationYear', 'education_year');
	}else{
		return array();
	}
}

function rtna_get_classroom_option(){
	if(db_exist_table('rtna_classroom')){
		return db_select_single_column('rtna_classroom', 'classroom');
	}else{
		return array();
	}
}

?>