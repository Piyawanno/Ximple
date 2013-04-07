<?php

function theme_get_info_voip(){
	return array(
		'name' => 'VoIP Solution',
		'description' => tt('Fixed width, 1 and 2 columns, tableless.'),
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
