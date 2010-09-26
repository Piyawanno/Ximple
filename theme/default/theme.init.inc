<?php

function theme_get_info_default(){
	$description = tt('Default and reference theme for Ximple.');
	$description.= tt('Fixed or fluid width, 2 or 3 columns, tableless, recolorable, flexible and highly configurable.');
	$description.= tt('The theme can be applied for many purposes.');
	return array(
		'name' => 'FlexiFun',
		'description' =>  $description,
		'preview' => 'preview.png',
		'block_position' => array(
			'left' => 'Left Sidebar',
			'right' => 'Right Sidebar',
			'header' => 'Header',
			'top' => 'Content Top',
			'bottom' => 'Content Bottom',
			'foot' => 'Foot',
		),
		'block_primary_position' => 'left',
		'menu_include_block' => true,
		'additional_config' => array(
			
		),
	);
}

?>
