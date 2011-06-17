<?php
/// @file
/// This file provides bootstrap functions and module execution with cache management for Ximple.
///
/// @author bow_der_kleine <bow_der_kleine@yahoo.de>


/// Initialize Ximple environment.
function main_init(){
	define('XIMPLE_CMS', 'initialized');
	main_handle_install();
	main_get_setup();
	main_handle_maintain();
	main_include();
	main_count_visitor();
	main_init_config();
	db_init();
	extension_execute('main_init');
	main_set_time_zone();
	main_init_var();
	main_handle_drop();
	authority();
	translate_define_language();
	config_translate();
	translate_add_directory(ROOT_PATH.'theme/'.cc('theme'));
}

function main_exec(){
	extension_execute('pre_main_exec');
	$cache_file = cache_get_page_file();
	if(cache_check_page($cache_file)){
		cache_show_page($cache_file);
	}else{
		$render = main_render();
		$render = postrender_correct_uri($render);
		cache_save_page($render, $cache_file);
		$render = postrender_get_read_number($render);
		$render = postrender_get_site_info($render);
		echo($render);
	}
	notify_save();
}

function main_render(){
	include('head.tool.inc');
	include('syswidget.tool.inc');
	include('userinfo.tool.inc');
	include('sectioninfo.tool.inc');
	include('search.tool.inc');
	document_set_path(cc('home_label'), '');
	extension_execute('pre_main_render');
	$body = execute(MODE);
	if(execute_as_site()){
		header('Content-Type: text/html; charset=UTF-8');
		$render = main_render_site($body);
	}elseif(execute_as_db()){
		header('Content-Type: text/html; charset=UTF-8');
		$render = main_render_db();
	}elseif(execute_as_ajax()){
		header('Content-Type: text; charset=UTF-8');
		$render = $body;
	}elseif(execute_as_print()){
		header('Content-Type: text/html; charset=UTF-8');
		$render = main_render_print($body);
	}
	$render = extension_execute('post_main_render', $render, $render);
	return $render;
}

function main_render_site($body){
	include_once('menu.tool.inc');
	include_once('widget.tool.inc');
	search_increase_point();
	$body = extension_execute('pre_main_render_site', $body, $body);
	$render_array = array(
		'body' => $body,
		'path' => document_render_path(),
		'section_name' => cc('section_name'),
		'section_slogan' => cc('section_slogan'),
		'menu' => menu_render(),
		'widget' => widget_render(),
		'notify' => notify_render(),
		'head' => head_render(),
	);
	search_add_source_page($body);
	$render = render($render_array, 'main.tpl', 'main');
	return $render;
}

function main_render_print($body){
	$render_array = array(
		'body' => $body,
		'section_name' => cc('section_name'),
		'section_slogan' => cc('section_slogan'),
		'head' => head_render_print(),
	);
	$render = render($render_array, 'print.tpl', 'print');
	return $render;
}

function main_count_visitor(){
	$authority = ss('authority');
	if(empty($authority)) count_increase('site', 0);
}

/// Get setup values from setup file.
function main_get_setup(){
	include(dirname(dirname(__FILE__)).'/setup.php');
}

/// Include necessary tools.
function main_include(){
	include('io.tool.inc');
	include('error.tool.inc');
	include('render.tool.inc');
	include('cache.tool.inc');
	include('authority.tool.inc');
	include('postrender.tool.inc');
	include('extension.tool.inc');
	include('execute.tool.inc');
	include('notify.tool.inc');
	include('document.tool.inc');
	include('config.tool.inc');
	include('input.tool.inc');
	include('count.tool.inc');
	include('translate.tool.inc');
	include(ROOT_PATH.'include/database/'.DB_TYPE.'.inc');
	if(!function_exists('mime_content_type')){
		include_once('external/upgradephp/ext/mime.php');
	}
}

/// Check the installation of Ximple on server.
function main_handle_install(){
	$root_path = dirname(dirname(dirname(__FILE__))).'/';
	if(state_is_install() or !is_file($root_path.'include/setup.php')){
		include('error.tool.inc');
		include('render.tool.inc');
		define('ROOT_PATH', $root_path);
		$root_uri = 'http://'.$_SERVER['HTTP_HOST'].dirname($_SERVER['PHP_SELF']).'/';
		define('ROOT_URI', $root_uri);
		$error = 'Ximple is not installed on your system, please try to <a href="'.$root_uri.'install">install</a>';
		error_fatal('Ximple is not installed.', $error);
	}
}

/// Check and handle maintain state of section.
function main_handle_maintain(){
	if(state_is_maintain()){
		include('error.tool.inc');
		include('render.tool.inc');
		$error = 'We are under maintenance, please be patient.';
		error_fatal('Under maintenance', $error);
	}
}

function main_handle_drop(){
	if(preg_match('/drop/', MODE) and gg('confirm') != "true"){
		$confirm = SMART_URI ? '/confirm/true' : '&confirm=true';
		$render_data = array(
			'redirect' => '',
			'check_drop' => true,
			'confirm_uri' => vv('REQUEST_URI').$confirm,
			'is_develop' => state_is_develop(),
		);
		$render = render($render_data, 'redirect.tpl', 'main_handle_drop');
		die($render);
	}
}

function main_render_db(){
	$redirect = document_get_redirect();
	if(document_get_redirect_back()) $redirect = vv('HTTP_REFERER');
	elseif(substr($redirect, 0, 1) == '?') $redirect = SECTION_URI.$redirect;
	elseif(strlen($redirect)) $redirect = SECTION_URI.Q.$redirect;
	else $redirect = SECTION_URI;
	$confirm = SMART_URI ? '/confirm/true' : '&confirm=true';
	$render_data = array(
		'redirect' => $redirect,
		'check_drop' => preg_match('/drop/', MODE) and gg('confirm') != "true",
		'confirm_uri' => vv('REQUEST_URI').$confirm,
		'is_develop' => state_is_develop(),
	);
	$render = render($render_data, 'redirect.tpl', 'db_redirect');
	echo($render);
}


/// Get configuration array of SECTION
/// @param $section : SECTION-ID
function main_init_config(){
	$GLOBALS['config'] = io_unserialize(ROOT_PATH.'files/config/config'.SECTION);
	$GLOBALS['config'] = config_check_default($GLOBALS['config']);
}


/// Initialize global variables.
function main_init_var(){
	$_SESSION['xblc_section'] = SECTION;
	unset($_SESSION['is_admin']);
	
	define('NOW', date('Y-m-d H:i:s'));
	define('TODAY', date('d F Y'));
	
	$language = ss('language');
	if(strlen($language)) $language = $language.'/';
	
	if(cc('friendly_url_enable')) define('Q', ''.$language);
	else define('Q', '?/'.$language);
	main_init_section_uri();
	main_init_uri_param();
}

/// Initialize constant SECTION_URI.
function main_init_section_uri(){
	if(SECTION == 1){
		define('SECTION_URI', ROOT_URI);
	}elseif(!defined('SECTION_URI')){
		if(isset($config['section_uri']) and strlen($config['section_uri'])){
			define('SECTION_URI', cc('section_uri'));
		}else{
			define('SECTION_URI', ROOT_URI.'section/'.cc('section_path').'/');
		}
	}
}

function main_init_uri_param(){
	$get = gg();
	define('IS_INDEX', count($get) == 0);
	$get_value = array_values($get);
	if(count($get) == 1 and strlen($get_value[0]) == 0){
		$process_get = main_process_smart_uri();
	}else{
		$process_get = main_process_common_uri();
	}
	$process_get = main_check_mode($process_get);
	$module = split('_', MODE);
	define('MODULE', $module[0]);
	define('MODE_ID', $process_get['id']);
	define('MODE_PAGE', $process_get['page']);
	$_GET = $process_get;
	globalvar_reset_get();
}

function main_process_smart_uri(){
	$key = array_keys(gg());
	if(count($key)) $query_string = $key[0];
	else $query_string = '';
	$uri_get = execute_parse_smart_uri($query_string);
	$uri_server = execute_parse_smart_uri(vv('QUERY_STRING'));
	$uri = input_special_char($uri_get, $uri_server);
	define('MODE', $uri['mode']);
	define('ORIG_REQUEST', substr(vv('QUERY_STRING'),1));
	define('SMART_URI', true);
	return $uri;
}

function main_process_common_uri(){
	$get = gg();
	if(isset($get['mode'])) define('MODE', $get['mode']);
	else define('MODE', cc('index_mode'));
	main_define_orig_request();
	define('SMART_URI', false);
	return $get;
}

function main_define_orig_request(){
	$get = gg();
	if(count($get)){
		$orig_request = '?';
		foreach($get as $key=>$value){
			$orig_request .= $key.'='.$value.'&';
		}
		define('ORIG_REQUEST', $orig_request);
	}else{
		define('ORIG_REQUEST', '');
	}
}

function main_check_mode($process_get){
	if(!isset($process_get['id'])) $process_get['id'] = '0';
	if(!isset($process_get['page'])) $process_get['page'] = '0';
	if(!ctype_digit($process_get['id'])) error_syslog(tt('Invalid MODE_ID'));
	if(!ctype_digit($process_get['page'])) error_syslog(tt('Invalid MODE_PAGE'));
	return $process_get;
}

function main_set_time_zone(){
	date_default_timezone_set(cc('time_zone'));
}
?>
