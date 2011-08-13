<?php

function theme_get_info_manam(){
	return array(
		'name' => 'Manam Thaifood',
		'description' => tt('Fixed width, 1 column, tableless, white color, not configurable, designed for Manam Thaifood Mini-Resteraunt.'),
		'preview' => 'preview.png',
		'widget_position' => array(
			'panel' => 'Control Panel',
			'foot' => 'Foot',
		),
		'widget_primary_position' => 'panel',
		'menu_include_widget' => false,
	);
}

?>
