<?php

function theme_get_info_wrest(){
	return array(
		'name' => 'WREST',
		'description' => tt('Fixed width, 2 columns, tableless, violet color, not configurable, designed for WREST Thai Women Networks.'),
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
