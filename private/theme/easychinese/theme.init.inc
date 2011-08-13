<?php

function theme_get_info_easychinese(){
	return array(
		'name' => 'Easy look in Chinese style',
		'description' => tt('Fixed width, 2 columns, tableless, red color, configurable, designed for Chinese community web-site.'),
		'preview' => 'preview.png',
		'widget_position' => array(
			'head' => 'Head',
			'left' => 'Left Sidebar',
			'foot' => 'Foot',
		),
		'widget_primary_position' => 'left',
		'menu_include_widget' => false,
	);
}

?>
