<?php
/// @file
/// This file provides installation-script for Ximple.
///
/// @author bow_der_kleine <bow_der_kleine@yahoo.de>

include('install.tool.inc');
install_boot();

function install_boot(){
	session_start();
	include_once('../include/tool/setini.tool.inc');
	setini();
	header('Content-Type: text/html; charset=UTF-8');
	install_check_setup();
	install_main();
}

/// Check the existence of setup.php.
/// If setup.php does not exist, the constants are temporally defined.
function install_check_setup(){
	global $agree;
	install_set_lang();
	if(is_file(dirname(__FILE__).'/../include/setup.php')){
		require_once('../include/setup.php');
	}else{
		install_error_setup_not_exist();
	}
}

/// Main function for Ximple installation.
/// @param $warn : warning message from check_setup().
function install_main(){
	install_define_constant();
	if(isset($_GET['mode'])) $function = 'install_'.$_GET['mode'];
	else $function = 'install_step0';
	if(!function_exists($function)) list($title, $body) =install_step0();
	else list($title, $body) = $function();
	$select_langauge = install_language_selection();
	$step = install_step_render();
	include('template/install.tpl');
}

/// Step 0 of installation : License agreement and check existence of setup.php.
function install_step0(){
	$handle = fopen('../LICENSE.txt', 'r');
	$license = fread ($handle, filesize ('../LICENSE.txt'));
	fclose($handle);
	$redner = '<h2>Step 0 : '.tt('License agreement').'</h2><pre>'.$license.'</pre>';
	$redner .=  '
	<form action="index.php" method="get">
		<input type="hidden" name="mode" value="step1"/>
		<input type="submit" value="'.tt('I agree').'">
	</form>';
	return array('Step 0 : '.tt('License agreement'), $redner);
}

/// Step 1 of installation : check constants in setup.php.
function install_step1(){
	$page = '<h2>Step 1 : '.tt('Setup validation').'</h2>';
	$page.= '<p>';
	
	list($next_enable_1, $result) = install_check_database();
	$page .= $result;
	list($next_enable_2, $result) = install_check_path();
	$page .= $result;
	list($next_enable_3, $result) = install_check_uri();
	$page .= $result;
	list($next_enable_4, $result) = install_check_lang();
	$page .= $result;
	
	if(!($next_enable_1 and $next_enable_2 and $next_enable_3 and $next_enable_4)){
		$next_enable = 'disabled="disabled"';
		$try = '<input type="button" value="'.tt('Try again').'" onclick="location.reload(true)">';
		$messsage = tt('You have to edit <b>%s</b> to correct invalid constants.');
		$page.= '<p>'.sprintf($messsage, ROOT_PATH.'include/setup.php').'</p>';
	}else{
		$next_enable = '';
		$try = '';
	}
	$next_step = 2;
	$page .= '</p>'.install_render_next_step($next_step, $next_enable, $try);
	return array('Step 1 : '.tt('Setup validation'), $page);
}

/// Step 2 of installation : check files and folders permissions.
function install_step2(){
	$title = 'Step 2 : '.tt('Permission validation');
	$page = '<h2>'.$title.'</h2>';
	$path = array('files', 'section');
	foreach($path as $item){
		$item = ROOT_PATH.$item;
		if((fileperms($item) & 0x0002)){
			$page.='<b>'.$item.' :</b> <b class="valid">OK</b><br />';
			$next_enable = '';
		}
		else{
			$page.='<b>'.$item.' :</b> <b class="invalid">Invalid !!! Please change to 0757</b><br />';
			$next_enable = 'disabled="disabled"';
		}
	}
	
	if($next_enable != 'disabled="disabled"'){
		$to_mkdir = install_directory_list();
		foreach($to_mkdir as $item){
			if(!is_dir(ROOT_PATH.$item)) mkdir(ROOT_PATH.$item);
		}
		$des = ROOT_PATH.'files/misc/ximple.png';
		if(!is_file($des)) copy(ROOT_PATH.'files/ximple.png', $des);
		$des = ROOT_PATH.'files/avatar/default.png';
		if(!is_file($des)) copy(ROOT_PATH.'files/default.png', $des);
	}
	
	if($next_enable != 'disabled="disabled"') $try = '';
	else $try = '<input type="button" value="'.tt('Try again').'" onclick="location.reload(true)">';
	
	$next_step = 3;
	$page.= '</p><br />'.install_render_next_step($next_step, $next_enable, $try);
	return array($title, $page);
}

/// Step 3 of installation : render form to get root-login information.
function install_step3(){
	$title = 'Step 3 : '.tt('Root-Login information');
	install_create_db_table();
	ob_start();
	require('template/user.tpl');
	$page = ob_get_contents();
	ob_end_clean();
	return array($title, $page);
}

/// Step 4 of installation : initial system and get minimal configuration.
function install_step4(){
	$title = 'Step 4 : '.tt('Configuration');
	install_insert_user();
	install_login();
	$page  = '<h2>'.$title.'</h2>'.install_section_config_page();
	return array($title, $page);
}

/// Step 5 of installation : save configuration and run pre-configuration script.
function install_step5(){
	include('preconfig.inc');
	install_init_section();
	install_init_authority();
	$function_name = 'preconfig_'.pp('preconfig');
	$function_name();
	block_init_default();
	$title = tt('Happy Ending').' : '.tt('Ximple has been successfully installed');
	$page  = '<h2>'.$title.'</h2>';
	$page .= install_finish_message();
	io_write_file(ROOT_PATH.'files/state/install', "");
	$state_dir = ROOT_PATH.'/files/state/1/';
	if(!is_dir($state_dir)) mkdir($state_dir);
	io_write_file($state_dir.'product', "");
	return array(tt('Happy Ending'), $page);
}
?>
