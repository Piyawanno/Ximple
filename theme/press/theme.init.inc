<?php

function theme_get_info_press(){
	return array(
		'name' => 'Press Machine',
		'description' => tt('Fixed width, 2 columns, tableless.'),
		'preview' => 'preview.png',
		'widget_position' => array(
			'right' => 'Right Sidebar',
			'foot' => 'Foot',
		),
		'widget_primary_position' => 'right',
		'menu_include_widget' => true,
	);
}

?>
