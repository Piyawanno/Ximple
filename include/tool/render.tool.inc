<?php

global $render_cache_tpl;

$render_cache_tpl = array();

function render($data, $tpl, $id){
	foreach($data as $key => $value){
		$$key = $value;
	}
	$tpl = render_get_tpl($tpl);
	ob_start();
	require($tpl);
	$render = ob_get_contents();
	ob_end_clean();
	return $render;
}

function render_get_tpl($tpl){
	global $render_cache_tpl;
	
	if(isset($render_cache_tpl[$tpl])){
		return $render_cache_tpl[$tpl];
	}
	
	$tpl_sys = ROOT_PATH.'theme/default/systemtemplate/'.$tpl;
	$tpl_module_sys = ROOT_PATH.'module/'.MODULE.'/systemtheme/'.$tpl;
	$tpl_theme = ROOT_PATH.'theme/'.cc('theme').'/template/'.$tpl;
	$tpl_default = ROOT_PATH.'theme/default/template/'.$tpl;
	$tpl_module = ROOT_PATH.'module/'.MODULE.'/theme/'.$tpl;
	$tpl_abs = ROOT_PATH.$tpl;
	
	if(is_file($tpl_sys)) $tpl_out = $tpl_sys;
	elseif(is_file($tpl_module_sys)) $tpl_out = $tpl_module_sys;
	elseif(is_file($tpl_theme)) $tpl_out = $tpl_theme;
	elseif(is_file($tpl_default)) $tpl_out = $tpl_default;
	elseif(is_file($tpl_module)) $tpl_out = $tpl_module;
	elseif(is_file($tpl_abs)) $tpl_out = $tpl_abs;
	else{
		$tpl_out = render_find_tpl($tpl);
		if($tpl_out == null){
			if(state_is_develop()) die('Template file can not be found : '.$tpl);
			else die();
		}
	}
	
	$render_cache_tpl[$tpl] = $tpl_out;
	return $tpl_out;
}

function render_find_tpl($tpl){
	$included_files = get_included_files();
	$included_dir = array();
	foreach($included_files as $value){
		$included_dir[] = dirname($value);
	}
	$included_dir = array_unique($included_dir);
	foreach($included_dir as $value){	
		$tpl_path = $value.'/theme/'.$tpl;
		if(is_file($tpl_path)){
			return $tpl_path;
		}
	}
	return null;
}

function render_icon($mode, $icon, $title){
	return '
	<a href="'.SECTION_URI.Q.$mode.'" >
		<img src="'.ROOT_URI.$icon.'" border="0" align="left" style="margin-right:5px;margin-left:5px;">
		<strong>'.$title.'</strong>
	</a>';
}

function render_write_icon($mode, $title){
	return '<p>'.render_icon($mode, 'files/icon/add.png', $title).'</p>';
}

function render_file_size($size){
	if($size > 1e8) return sprintf('%.1f GB', $size/1e9);
	elseif($size > 1e5) return sprintf('%.1f MB', $size/1e6);
	else return sprintf('%.1f kB', $size/1e3);
}

function render_profile_link($user){
	if($user['id'] == -1) return $user['login_name'];
	else return '<a href="'.SECTION_URI.Q.'profile/'.$user['id'].'">'.$user['login_name'].'</a>';
}

function render_avatar($user){
	return '
	<p align="center">
		<a href="'.SECTION_URI.Q.'profile/'.$user['id'].'">
			<img src="'.ROOT_URI.$user['avatar'].'" border="0" />
		</a>
	</p>
	<p align="center">'.render_profile_link($user).'</p>';
}

function render_category_icon($category, $mode){
	return '
	<p align="center">
		<a href="'.SECTION_URI.Q.$mode.'/tag/'.$category['category'].'">
			<img src="'.ROOT_URI.$category['pic'].'" border="0" />
		</a>
	</p>
	<p align="center">
		<a href="'.SECTION_URI.Q.$mode.'/tag/'.$category['category'].'">'.$category['category'].'</a>
	</p>
	';
}

function render_search_form(){
	return '
	<form action="'.SECTION_URI.'" method="GET">
		<input name="mode" type="hidden" value="search"/>
		<input name="search" size="30" id="search_input"/>
		<input type="submit" value="'.tt('search').'" id="search_submit" />
	</form>';
}

function render_uri($mode, $data){
	if(strlen($data['uri'])) return SECTION_URI.Q.$mode.'/'.$data['id'].'/'.$data['uri'].'.html';
	else return SECTION_URI.Q.$mode.'/'.$data['id'];
}
?>
