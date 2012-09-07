<?php
function rtna_get_cadet_uid_option(){
	$all_cadet = userinfo_get_login_name_by_role('rtna_cadet');
	$clause = 'WHERE section='.SECTION;
	$exist_uid = db_select_single_column('rtna_cadet', 'uid', $clause);
	foreach($exist_uid as $key => $value){
		unset($all_cadet[$value]);
	}
	return $all_cadet;
}

function rtna_get_yearserie_option(){
	if(db_exist_table('rtna_yearserie')){
		return db_select_single_column('rtna_yearserie', 'serie_number');
	}else{
		return array();
	}
}

<<<<<<< HEAD
=======
function rtna_get_faculty_option(){
	if(db_exist_table('rtna_faculty')){
		return db_select_single_column('rtna_faculty', 'faculty');
	}else{
		return array();
	}
}
>>>>>>> 61364f51ab11c6241cee9f94dfdfcbd4e032030d
function rtna_get_cadet_party_option(){
	return array(
		0 => tt('undefined'),
		1 => tt('naval'),
		2 => tt('mechanical'),
	);
}


<<<<<<< HEAD
?>
=======
?>

>>>>>>> 61364f51ab11c6241cee9f94dfdfcbd4e032030d
