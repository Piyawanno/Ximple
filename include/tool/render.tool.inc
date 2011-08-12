<?php
global $render_cache_tpl;

$render_cache_tpl = array();

function render($data, $tpl, $id){
	foreach($data as $key => $value){
		$$key = $value;
	}
	$tpl = render_get_tpl($tpl);
	ob_start();
	if(is_file($tpl)) require($tpl);
	$render = ob_get_contents();
	ob_end_clean();
	return $render;
}

function render_get_tpl($tpl){
	global $render_cache_tpl;
	
	if(isset($render_cache_tpl[$tpl])){
		return $render_cache_tpl[$tpl];
	}
	
	$tpl_sys = THEME_PATH.'default/systemtemplate/'.$tpl;
	$tpl_module_sys = MODULE_PATH.MODULE.'/systemtheme/'.$tpl;
	$tpl_private = SECTION_PATH.'private/theme/'.cc('theme').'/template/'.$tpl;
	$tpl_theme = THEME_PATH.cc('theme').'/template/'.$tpl;
	$tpl_default = THEME_PATH.'default/template/'.$tpl;
	$tpl_module = MODULE_PATH.MODULE.'/theme/'.$tpl;
	$tpl_abs = ROOT_PATH.$tpl;
	
	if(is_file($tpl_sys)) $tpl_out = $tpl_sys;
	elseif(is_file($tpl_module_sys)) $tpl_out = $tpl_module_sys;
	elseif(is_file($tpl_private)) $tpl_out = $tpl_private;
	elseif(is_file($tpl_theme)) $tpl_out = $tpl_theme;
	elseif(is_file($tpl_default)) $tpl_out = $tpl_default;
	elseif(is_file($tpl_module)) $tpl_out = $tpl_module;
	elseif(is_file($tpl_abs)) $tpl_out = $tpl_abs;
	else{
		$tpl_out = render_find_tpl($tpl);
		if($tpl_out == null){
			echo('Template file can not be found : '.$tpl_out);
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

function render_tag($category, $freetag, $mode){
	$render = '';
	if(isset($category['category']) and isset($category['reference'])){
		$reference = $category['reference'];
		$label = $category['category'];
		$render .= '<a href="'.SECTION_URI.Q.$mode.'/tag/'.$reference.'/tag_label/'.$label.'">'.$label.'</a> ';
	}else{
		$label = null;
	}
	foreach($freetag as $key => $value){
		if($value != $label){
			$render .= '<a href="'.SECTION_URI.Q.$mode.'/tag/'.$value.'">'.$value.'</a> ';
		}
	}
	return $render;
}

function render_icon($mode, $icon, $title){
	return '
	<a href="'.SECTION_URI.Q.$mode.'" class="write_icon">
		<img src="'.ROOT_URI.$icon.'" border="0" >
		'.$title.'
	</a>';
}

function render_ajax_icon($onclick, $icon, $title){
	return '
	<a href="#" onclick="return '.$onclick.'()" class="write_icon">
		<img src="'.ROOT_URI.$icon.'" border="0" align="left">
		'.$title.'
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

function render_profile_link($user, $attribute=null){
	if($user['id'] == -1) return $user['login_name'];
	else return '<a href="'.SECTION_URI.Q.'profile/'.$user['id'].'" '.$attribute.'>'.$user['login_name'].'</a>';
}

function render_signature($user){
	if(isset($user['config']['signature'])){
		$signature = $user['config']['signature'];
	}else{
		$signature = null;
	}
	if(strlen($signature)){
		return '<p class="signature">['.$signature.']</p>';
	}
}

function render_avatar($user, $show_profile=true){
	if(strlen($user['avatar']) == 0) $user['avatar'] = 'files/default.png';
	
	if($user['id'] > 0) $uri = SECTION_URI.Q.'profile/'.$user['id'];
	elseif(authority_is_guest()) $uri = '';
	else $uri = SECTION_URI.Q.'profile_write_mail/send_to_address/'.$user['email'];
	
	$render = '
	<p align="center">
		<a href="'.$uri.'">
			<img src="'.ROOT_URI.$user['avatar'].'" border="0" />
		</a>
	</p>';
	if($show_profile){
		$render .= '<p align="center">'.render_profile_link($user).'</p>';
	}
	return $render;
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

function render_option($data){
	return '<option>'.join('</option><option>', $data).'</option>';
}

function render_operation_link($mode, $id, $label){
	return '<a href="'.SECTION_URI.Q.$mode.'/'.$id.'">'.$label.'</a>';
}

function render_print_link($print_mode){
	return '<a href="'.SECTION_URI.Q.$print_mode.'" onclick="ximplePrint(this); return false;">'.tt('print').'</a>';
}

function render_raw_link($uri){
	if(substr($uri, 0, 7) != 'http://') $uri = 'http://'.$uri;
	return "<a href=\"$uri\">$uri</a>";
}

function render_tag_cloud($mode, $freetag){
	if($freetag['number'] < 520){
		$size = 12 + $freetag['number']/10;
	}else{
		$size = 64;
	}
	$href = SECTION_URI.Q.$mode.'/tag/'.$freetag['freetag'];
	return '<a href="'.$href.'" style="font-size:'.$size.'px;">'.$freetag['freetag'].'</a>';
}

function render_calendar($data, $mode, $month, $year){
	head_add_css('calendar.css');
	$time = strtotime("$year-$month-01");
	
	if($month == 1){
		$prev_month = 12;
		$prev_year = $year - 1;
	}else{
		$prev_month = $month - 1;
		$prev_year = $year;
	}
	
	if($month == 2){
		$next_month = 1;
		$next_year = $year + 1;
	}else{
		$next_month = $month + 1;
		$next_year = $year;
	}
	
	$render_array = array(
		'data' => $data,
		'mode' => $mode,
		'first_day' => date('w', $time),
		'day_number' => date('t', $time),
		'today' => date('Y-n-j'),
		'month' => $month,
		'month_name' => date('F', $time),
		'year' => $year,
		'prev_month' => $prev_month,
		'prev_year' => $prev_year,
		'next_month' => $next_month,
		'next_year' => $next_year,
	);
	return render($render_array, 'calendar.tpl', 'calendar');
}
?>
