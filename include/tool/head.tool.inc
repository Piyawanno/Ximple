<?php
/// @file
/// This file provides functions for rendering HTML-header meta-information and
/// including javascript and css.
///
/// @author Kittipong Piyawanno <k.piyawanno@gmail.com>

/// Internal global variables for head-tool.
/// These variables should not be used outside this file.
global $head_css, $head_js, $head_js_array;
global $head_js_var, $head_print_css;
global $head_injected_js;

$head_css = array(
	head_get_css_uri('main.css'),
	head_get_css_uri('common.css'),
);

$head_print_css = array(
	'print.css'
);

$head_js = array(
	'include/external/jquery/jquery.js',
	'include/external/jquery/jquery-ui.js',
	'include/javascript/main.js'
);

$head_js_var = array(
	'rootURI' => ROOT_URI,
	'translateModuleName' => null,
	'modeName' => MODE,
	'sectionID' => SECTION,
	'sectionURI' => SECTION_URI.Q,
	'sectionURICommon' => SECTION_URI,
	'themeURI' => THEME_URI,
	'checkNotifyInterval' => cc('notify_interval')*1000,
	'isGuest' => authority_is_guest(),
	'autoCompleteTop' => 0,
	'autoCompleteLeft' => 0,
	'isForm' => false,
);

$head_js_array = array();
$head_injected_js = '';

/// Render HTML-header with meta information and including javascript and css.
function head_render(){
	if(IS_APC and $cache = apc_fetch('head_'.CACHE_PAGE_FILE)) return $cache;
	$head='
		<title>'.head_get_document_title().'</title>
		<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
		<meta name="keywords" content="'.document_get_keywords().'" />
		<meta name="description" content="'.document_get_description().'" />
		<link rel="shortcut icon" href="'.ROOT_URI.cc('icon').'" type="image/png" />
		'.head_include_feed_link().'
		'.head_include_main_css().'
		'.head_define_js_var().'
		'.head_define_js_array().'
		'.head_include_js().'
		'.head_render_injected_js().'
		'.cc('meta_data');
	if(IS_APC) apc_add('head_'.CACHE_PAGE_FILE, $head);
	return $head;
}

/// Render HTML-header with meta information and including javascript and css for printing document.
function head_render_print(){
	$head='
		<title>'.head_get_document_title().'</title>
		<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
		<link rel="shortcut icon" href="'.ROOT_URI.cc('icon').'" type="image/png" />
		'.head_include_print_css();
	return $head;
}


/// Get document title for meta information.
function head_get_document_title(){
	if(IS_INDEX) $title = cc('section_name').' : '.cc('section_slogan');
	else $title = document_get_title().' : '.cc('section_name');
	return $title;
}

/// Generate head information about feed link dependent on SECTION configuration.
/// @return Link to feed documents.
function head_include_feed_link(){
	$feed_link = '';
	$feed_type = cc('feed_type');
	$comment_explicit = cc('feed_comment_explicit');
	if(is_array($feed_type)){
		$alternate = "\n".'<link rel="alternate" type="application/%s+xml" title="%s" href="'.ROOT_URI.'files/xml/'.SECTION.'/%s.xml" />';
		if(in_array('rss', $feed_type)){
			$feed_link .= sprintf($alternate, 'rss', 'RSS 2.0', 'rss');
		}
		if(in_array('atom', $feed_type)){
			$feed_link .= sprintf($alternate, 'atom', 'Atom', 'atom');
		}
		if(in_array('rss', $feed_type) and $comment_explicit){
			$feed_link .= sprintf($alternate, 'rss', 'RSS Comment', 'rss_comment_');
		}
		if(in_array('atom', $feed_type) and $comment_explicit){
			$feed_link .= sprintf($alternate, 'atom', 'Atom Comment', 'atom_comment_');
		}
	}
	return $feed_link;
}

/// Define javascript variables with PHP-information.
/// @return Definition of javascript variables.
function head_define_js_var(){
	global $head_js_var;
	$js_var = '';
	foreach($head_js_var as $key => $value){
		if($value == null) $js_var .= 'var '.$key.' = null;';
		elseif(is_string($value)) $js_var .= 'var '.$key.' = "'.$value.'";'."\n\t\t";
		elseif(is_bool($value)) $js_var .= 'var '.$key.' = '.($value?'true':'false').';'."\n\t\t";
		else $js_var .= 'var '.$key.' = '.$value.';'."\n\t\t";
	}
	return "<script type=\"text/javascript\">\n$js_var</script>";
}

/// Add javascript variables into document.
/// @param $name : variable name.
/// @param $value : variable value.
function head_add_js_var($name, $value){
	global $head_js_var;
	$head_js_var[$name] = $value;
}

/// Define javascript array with PHP-information.
/// @return Definition of javascript variables.
function head_define_js_array(){
	global $head_js_array;
	$js_var = '';
	foreach($head_js_array as $name => $array){
		$js_var .= 'var '.$name." = new Array();\n";
		foreach($array as $key => $value){
			$js_var .= "\n".$name.'["'.$key.'"] = "'.$value.'";'."\n\t\t";
		}
	}
	return '<script type="text/javascript">'.$js_var.'</script>';
}

/// Add javascript array into document.
/// @param $name : variable name.
/// @param $value : variable value.
function head_add_js_array($name, $value){
	global $head_js_array;
	$head_js_array[$name] = $value;
}


/// Execution of adding javascript into document.
/// @return Link to external javascripts
function head_include_js(){
	global $head_js;
	if(XIMPLE_THEME_MODE == 'MOBILE'){
		$head_js[] = 'include/external/jquery/jquery.mobile.js';
	}
	$link = '';
	foreach($head_js as $value){
		if(substr($value, 0, 7) != 'http://') $uri = ROOT_URI.$value;
		else $uri = $value;
		$link .= "\n\t\t";
		$link .= '<script type="text/javascript" src="'.$uri.'" ></script>';
	}
	return $link;
}


/// Add a javascript into document.
/// @param $js : relative path of javascript from ROOT_PATH
function head_add_js($js){
	global $head_js;
	if(!in_array($js, $head_js)){
		$head_js[] = $js;
	}
}

/// Inject JavaScript into Head Tag.
/// @param $js : JavaScript code to inject;
function head_inject_js($js){
	global $head_injected_js;
	$head_injected_js .= $js;
}

/// Render injected JavaScript into Head Tag.
/// @return Rendered injected JavaScript.
function head_render_injected_js(){
	global $head_injected_js;
	return '
	<script type="text/javascript">
		'.$head_injected_js.'
	</script>';
}

/// Render HTML-Tag to include CSS into main document.
/// @return Rendered HTML-Tag for CSS including.
function head_include_main_css(){
	global $head_css;
	if(XIMPLE_THEME_MODE == 'MOBILE'){
		$head_css[] = 'include/external/jquery/themes/jquery.mobile.css';
	}else{
		$jquery_css = 'theme/'.cc('theme').'/jquery/ui.all.css';
		if(is_file(ROOT_PATH.$jquery_css)){
			$head_css[] = $jquery_css;
		}elseif(is_file(SECTION_PATH.'private/'.$jquery_css)){
			$head_css[] = 'private/'.$jquery_css;
		}else{
			$head_css[] = 'include/external/jquery/themes/base/ui.all.css';
		}
	}
	return head_include_css($head_css);
}

/// Render HTML-Tag to include CSS into print document.
/// @return Rendered HTML-Tag for CSS including.
function head_include_print_css(){
	global $head_print_css;
	return head_include_css($head_print_css);
}

/// Execution of adding css into document.
/// @return Link to css style sheets.
function head_include_css($css){
	$link = '';
	foreach($css as $uri){
		$link .= "\n\t\t";
		$link .= '<link rel="stylesheet" type="text/css" href="'.$uri.'" />';
	}
	return $link;
}

/// Add a additional css into document.
/// @param $css : css filename.
function head_add_css($css){
	global $head_css;
	$css = head_get_css_uri($css);
	if(!in_array($css, $head_css)){
		$head_css[] = $css;
	}
}

/// Add a additional css into printing document.
/// @param $css : css filename.
function head_add_print_css($css){
	global $head_print_css;
	if(!in_array($css, $head_print_css)){
		$head_print_css[] = $css;
	}
}

/// Get URI of CSS dependent of configuration.
/// @param $file_name : file name of CSS.
/// @return URI of CSS.
function head_get_css_uri($file_name){
	if(XIMPLE_THEME_MODE != 'HTML4') $uri = head_get_css_mode_uri($file_name, XIMPLE_THEME_MODE.'/');
	if(empty($uri)) $uri = head_get_css_mode_uri($file_name, 'HTML4/');
	if(empty($uri)){
		$uri = header_find_css($file_name, XIMPLE_THEME_MODE.'/');
		if(strlen($uri)) $uri = ROOT_URI.$uri;
	}
	if(empty($uri)) $uri = ROOT_URI.header_find_css($file_name, 'HTML4/');
	return $uri;
}

function head_get_css_mode_uri($file_name, $mode){
	$module = globalvar_get_module();
	$path_custom = 'files/customtheme/'.SECTION.'/'.cc('theme').'/'.$mode.'css/'.$file_name;
	$path_private = 'private/theme/'.cc('theme').'/'.$mode.'css/'.$file_name;
	$path_private_module = 'private/module/'.$module.'/theme/'.$mode.'css/'.$file_name;
	$path_theme = 'theme/'.cc('theme').'/'.$mode.'css/'.$file_name;
	$path_default = 'theme/default/'.$mode.'css/'.$file_name;
	$path_module = 'module/'.$module.'/theme/'.$mode.'css/'.$file_name;
	
	if(is_file(ROOT_PATH.$path_custom)) return ROOT_URI.$path_custom;
	elseif(is_file(SECTION_PATH.$path_private)) return SECTION_URI.$path_private;
	elseif(is_file(SECTION_PATH.$path_private_module)) return SECTION_URI.$path_private_module;
	elseif(is_file(ROOT_PATH.$path_theme)) return ROOT_URI.$path_theme;
	elseif(is_file(ROOT_PATH.$path_default)) return ROOT_URI.$path_default;
	elseif(is_file(ROOT_PATH.$path_module)) return ROOT_URI.$path_module;
	elseif(is_file(ROOT_PATH.$file_name)) return ROOT_URI.$file_name;
	elseif(is_file(SECTION_PATH.$file_name)) return SECTION_URI.$file_name;
	else null;
}

/// Find CSS location dependent of configuration.
/// @param $file_name : file name of CSS.
/// @return Location of found CSS.
function header_find_css($file_name, $mode){
	$included_files = get_included_files();
	$included_dir = array();
	foreach($included_files as $value){
		$included_dir[] = dirname($value);
	}
	
	$included_dir = array_unique($included_dir);
	foreach($included_dir as $value){	
		$css_path = $value.'/theme/'.$mode.'css/'.$file_name;
		if(is_file($css_path)) return substr($css_path, strlen($included_dir[0]));
	}
	return null;
}
?>
