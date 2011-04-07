<?php
/// @file
/// This file provides functions for rendering HTML-header meta-information and
/// including javascript and css.
///
/// @author bow_der_kleine <bow_der_kleine@yahoo.de>

/// Internal global variables for head-tool.
/// These variables should not be used outside this file.

global $head_css, $head_js, $head_js_array, $head_js_var, $head_print_css;

$head_css = array(
	'main.css',
	'common.css',
	'include/external/jquery/themes/base/ui.all.css',
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
	'moduleName' => MODULE,
	'translateModuleName' => null,
	'modeName' => MODE,
	'modeID' => MODE_ID,
	'sectionID' => SECTION,
	'sectionURI' => SECTION_URI.Q,
	'sectionURICommon' => SECTION_URI,
	'checkNotifyInterval' => cc('notify_interval')*1000,
	'isGuest' => authority_is_guest(),
	'autoCompleteTop' => 0,
	'autoCompleteLeft' => 0,
);

$head_js_array = array();

/// Render HTML-header with meta information and including javascript and css.
function head_render(){
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
		'.cc('meta_data');
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
		if(empty($value)) $js_var .= 'var '.$key.' = null;';
		elseif(is_string($value)) $js_var .= 'var '.$key.' = "'.$value.'";'."\n\t\t";
		elseif(is_bool($value)) $js_var .= 'var '.$key.' = '.($value?'true':'false').';'."\n\t\t";
		else $js_var .= 'var '.$key.' = '.$value.';'."\n\t\t";
	}
	return '<script type="text/javascript">'.$js_var.'</script>';
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
	$link = '';
	foreach($head_js as $value){
		$link .= "\n\t\t";
		$link .= '<script type="text/javascript" src="'.ROOT_URI.$value.'" ></script>';
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

function head_include_main_css(){
	global $head_css;
	return head_include_css($head_css);
}

function head_include_print_css(){
	global $head_print_css;
	return head_include_css($head_print_css);
}

/// Execution of adding css into document.
/// @return Link to css style sheets.
function head_include_css($css){
	$link = '';
	foreach($css as $value){
		$uri = head_get_css_uri($value);
		$link .= "\n\t\t";
		$link .= '<link rel="stylesheet" type="text/css" href="'.$uri.'" />';
	}
	return $link;
}

/// Add a additional css into document.
/// @param $css : css filename.
function head_add_css($css){
	global $head_css;
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

function head_get_css_uri($file_name){
	$path_custom = 'files/customtheme/'.SECTION.'/'.cc('theme').'/css/'.$file_name;
	$path_theme = 'theme/'.cc('theme').'/css/'.$file_name;
	$path_default = 'theme/default/css/'.$file_name;
	$path_module = 'module/'.MODULE.'/theme/'.$file_name;
	
	if(is_file(ROOT_PATH.$path_custom)) return ROOT_URI.$path_custom;
	elseif(is_file(ROOT_PATH.$path_theme)) return ROOT_URI.$path_theme;
	elseif(is_file(ROOT_PATH.$path_default)) return ROOT_URI.$path_default;
	elseif(is_file(ROOT_PATH.$path_module)) return ROOT_URI.$path_module;
	elseif(is_file(ROOT_PATH.$file_name)) return ROOT_URI.$file_name;
	else return ROOT_URI.header_find_css($file_name);
}

function header_find_css($file_name){
	$included_files = get_included_files();
	$included_dir = array();
	foreach($included_files as $value){
		$included_dir[] = dirname($value);
	}
	$included_dir = array_unique($included_dir);
	foreach($included_dir as $value){	
		$css_path = $value.'/theme/'.$file_name;
		if(is_file($css_path)){
			return substr($css_path, strlen(ROOT_PATH));
		}
	}
	return null;
}
?>
