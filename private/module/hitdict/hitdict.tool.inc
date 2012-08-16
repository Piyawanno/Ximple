<?php
function hitdict_get_language_pair_option(){
	return array(
		'th_en' => tt('thai to english'),
		'en_th' => tt('english to thai'),
		'th_cn' => tt('thai to chinese'),
	);	
}

function hitdict_get_part_pair_option(){
	return array(
		'noun' => tt('noun'),
		'prnoun' => tt('pronoun'),
		'verb' => tt('verb'),
		'adverb' => tt('adverb'),
		'adjective' => tt('adjective'),
		'preposition' => tt('preposition'),
		'conjunction' => tt('conjunction'),
		'interjection' => tt('interjection'),		
	);
}

function hitdict_get_headword_option(){
	if(db_exist_table('hitdict')){
		$clause = 'WHERE section='.SECTION;
		return db_select_single_column('hitdict', 'headword', $clause);
	}
}
?>



