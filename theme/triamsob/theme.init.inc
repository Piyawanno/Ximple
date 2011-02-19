<?php

function theme_get_info_triamsob(){
	return array(
		'name' => 'TriamSob',
		'description' => tt('Fixed width, 3 columns, tableless, For TriamSob.Com.'),
		'preview' => 'preview.png',
		'block_position' => array(
			'middle' => 'Middle Sidebar',
			'right' => 'Right Sidebar',
			'foot' => 'Foot',
		),
		'block_primary_position' => 'middle',
		'menu_include_block' => true,
	);
}

?>
