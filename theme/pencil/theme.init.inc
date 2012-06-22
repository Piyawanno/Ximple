<?php

function theme_get_info_pencil(){
	return array(
		'name' => 'Pencil',
		'description' => tt('Fixed width, 2 columns, tableless.'),
		'preview' => 'preview.png',
		'widget_position' => array(
			'left' => 'Left Sidebar',
			'foot' => 'Foot',
		),
		'widget_primary_position' => 'left',
		'menu_include_widget' => true,
	);
}

?>
