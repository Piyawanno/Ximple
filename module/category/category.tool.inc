<?php
function category_init($mode){
	$exist = db_select_single_column('category', 'id', "WHERE mode='".$mode."' AND section=".SECTION);
	if(count($exist) == 0){
		$data = array(
			'category' => tt('uncategorized'),
			'description' => tt('This category is automatically initialized. You can edit it to make it more usable.'),
			'mode' => $mode,
			'section' => SECTION,
			'pic' => 'files/icon/uncategorized.png',
		);
		db_insert('category', $data);
	}
}
?>
