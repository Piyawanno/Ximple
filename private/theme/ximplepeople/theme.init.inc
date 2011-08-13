<?php
function theme_get_info_ximplepeople(){
	return array(
		'name' => 'Ximple People',
		'description' => tt('Fixed width, 1 columns, tableless, not configurable, designed for XimpleSoft website.'),
		'preview' => 'preview.png',
		'widget_position' => array(
			'left' => 'Left',
			'foot' => 'Foot',
		),
		'widget_primary_position' => 'left',
		'menu_include_widget' => true,
	);
}
?>
