<?php

execute_add_function('sysblock_login');
execute_add_function('sysblock_panel');
execute_add_function('sysblock_execute_info');
execute_add_function('sysblock_translate');
execute_add_function('sysblock_navigation');
execute_add_function('sysblock_navigation_config');
execute_add_function('sysblock_navigation_save');

function sysblock_login(){
	if(authority_is_guest()){
		$render_array = array(
			'forget_password' => cc('forget_password'),
			'registable' => cc('registable')
		);
		head_add_js('include/external/sha1.js');
		head_add_js('include/javascript/login.js');
		return render($render_array, 'loginform.tpl', 'loginform');
	}else{
		return render(array(), 'logoutform.tpl', 'logoutform');
	}
}

function sysblock_panel(){
	if(authority_is_guest()) return null;
	$cache_dir = cache_get_dir('panel');
	$cache_file = $cache_dir.USER_ID;
	if(is_file($cache_file) and 0) return io_read_file($cache_file);
	$render_data = array('panel' => sysblock_get_panel_array());
	$render = render($render_data, 'panel.tpl', 'panel');
	io_write_file($cache_file, $render);
	return $render;
}

function sysblock_navigation(){
	$navigation = cc('navigation');
	$navigation['home'] = cc('home_label');
	$navigation = translate_content($navigation, 'block', gg('id'));
	$navigation_enabled = array();
	foreach(cc('navigation_enabled') as $key){
		$navigation_enabled[$key] = $navigation[$key];
	}
	return render(array('data' => $navigation_enabled), 'navigation.tpl', 'navigation');
}

function sysblock_translate(){
	$render_array = array();
	$render_array['language'] = cc('supported_language');
	if(!is_array($render_array['language'])){
		$render_array['language'] = array();
	}
	return render($render_array, 'translateblock.tpl', 'translateblock');
}

function sysblock_navigation_config(){
	if(gg('is_translate') == 'false') return  sysblock_navigation_general_config();
	else return sysblock_navigation_translate_config();
}

function sysblock_navigation_general_config(){
	$navigation = cc('navigation');
	$navigation['home'] = cc('home_label');
	$modelCol = Model::checkedit(tt('enable edit and sort Navigation item'), $navigation);
	$modelCol->data = cc('navigation_enabled');
	$modelCol->isSortable = true;
	return array('navigation' => $modelCol);
}

function sysblock_navigation_translate_config(){
	$translated = translate_get_all_data('block', gg('module_id'), gg('language'));
	$navigation = cc('navigation');
	$form = array();
	foreach($navigation as $key => $value){
		$model = Model::char($value);
		if(isset($translated[$key])){
			$model->data = $translated[$key];
		}
		$form[$key] = $model;
	}
	return $form;
}

function sysblock_navigation_save(){
	$check_navigation = pp('check_navigation');
	$navigation = pp('navigation');
	$old_navigation = cc('navigation');
	$new_navigation = array();
	if(is_array($check_navigation)){
		foreach($check_navigation as $key => $value){
			$new_navigation[$value] = $navigation[$key];
			unset($old_navigation[$value]);
			if($value == 'home'){
				config_set('home_label', $navigation[$key]);
			}
		}
	}
	$new_navigation = array_merge($new_navigation, $old_navigation);
	config_set('navigation', $new_navigation);
	config_set('navigation_enabled', $check_navigation);
	config_save();
}

function sysblock_execute_info(){
	return '<!--{site_info}-->';
}


function sysblock_get_panel_array(){
	$panel = config_default_panel();
	if(authority_is_admin()){
		$panel = array_merge($panel, sysblock_get_admin_panel_array());
	}else{
		$panel = array_merge($panel, sysblock_get_user_panel_array());
	}
	ksort($panel);
	return $panel;
}

/// Processing panel array for admin.
/// @return Array of panel for admin.
function sysblock_get_admin_panel_array(){
	$panel_conf = sysblock_get_panel_config();
	$panel_out = array();
	foreach($panel_conf as $key => $panel){
		$items = array();
		foreach($panel as $acc_ref => $item){
			$items = array_merge($items, $item);
		}
		ksort($items);
		$panel_out[$key] = $items;
	}
	return $panel_out;
}

/// Processing panel array for regular user (no guest no admin).
/// @return Array of panel for regular user.
function sysblock_get_user_panel_array(){
	$panel_conf = sysblock_get_panel_config();
	$panel_out = array();
	$groups = ss('login_group');
	$groups[] = 3;
	foreach($panel_conf as $key => $panel){
		$items = array();
		foreach($panel as $acc_ref => $item){
			$ref_group = cc($acc_ref);
			if(is_array($ref_group) and count(array_intersect($groups, $ref_group))){
				$items = array_merge($items, $item);
			}
		}
		ksort($items);
		if(count($items)) $panel_out[$key] = $items;
	}
	return $panel_out;
}

function sysblock_get_panel_config(){
	$panel = io_unserialize(ROOT_PATH.'files/config/panel'.SECTION);
	if(!is_array($panel)) $panel = array();
	$panel = array_merge($panel, config_default_panel_access());
	return $panel;
}

function sysblock_get_list(){
	return array( 
		'primary' => array('sysblock_login', 'sysblock_panel', 'sysblock_navigation'),
		'secondary' => array('sysblock_execute_info'),
	);
}

?>
