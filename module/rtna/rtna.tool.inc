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
		return db_select_single_column('rtna_cadet', 'name');
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
		0 => tt('¹¹Ã.'),
	);
}
function rtna_get_officer_rank_option(){
	return array(
		1 => tt('Ã.µ.'), 
		2 => tt('Ã.·.'),
		3 => tt('Ã.Í.'),
		4 => tt('¹.µ.'),
		5 => tt('¹.·.'),
		6 => tt('¹.Í.'),
		7 => tt('¹.Í.(¾)'),
		8 => tt('¾Å.Ã.µ.'),
		9 => tt('¾Å.Ã.·.'),
		10 => tt('¾Å.Ã.Í.'),
		11 => tt('Ã.µ.(Ë­Ô§)'), //(Ë­Ô§)
		12 => tt('Ã.·.(Ë­Ô§)'),
		13 => tt('Ã.Í.(Ë­Ô§)'),
		14 => tt('¹.µ.(Ë­Ô§)'),
		15 => tt('¹.·.(Ë­Ô§)'),
		16 => tt('¹.Í.(Ë­Ô§)'),
		17 => tt('¹.Í.(¾)(Ë­Ô§)'),
		18 => tt('¾Å.Ã.µ.(Ë­Ô§)'),
		19 => tt('¾Å.Ã.·.(Ë­Ô§)'),
		20 => tt('¾Å.Ã.Í.(Ë­Ô§)'),
	);
}
?>
