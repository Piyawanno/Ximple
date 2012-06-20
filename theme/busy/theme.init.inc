<?php

function theme_get_info_busy(){
	return array(
		'name' => 'Business World',
		'description' => tt('Fixed width, 2 columns, tableless.'),
		'preview' => 'preview.png',
		'widget_position' => array(
			'top' => 'Header Highlight',
			'left' => 'Left Sidebar',
			'foot' => 'Foot',
		),
		'widget_primary_position' => 'left',
		'menu_include_widget' => true,
	);
}

?>
