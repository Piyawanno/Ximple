<?php
/// @file
/// This file provides installation-script for X-BLC.
///
/// @author bow_der_kleine <bow_der_kleine@yahoo.de>
session_start();
include_once('../include/setini.inc');
setini(1);
header('Content-Type: text/html; charset=UTF-8');
$warn = check_setup();
include_once('../include/preinclude.inc');
include_once('../include/include.inc');
main_install($warn);

$GLOBALS['ignore_db_syslog'] = true;

/// Main function for X-BLC installation.
/// @param $warn : warning message from check_setup().
function main_install($warn){
	global $config;
	global $agree;
	add_messages(__FILE__);
	
	if(!isset($_GET['mode']) or !function_exists($_GET['mode'])) list($title, $body) = step0();
	else list($title, $body) = $_GET['mode']();
	
	$body = $warn.$body;
	
	$config['section'] = 1;
	$config = get_by_install('../files/config/config/config'.$config['section'].'.inc');
	$config['mode'] = $config['index_mode'];
	$config['theme'] = 'admin';
	
	$select_langauge = language_selection();
	$step = step_render();
	include('template.inc');
}

/// Render selection for interface language selection.
function language_selection(){
	$lang = array(
		'en' => 'English',
		'th' => 'ภาษาไทย',
	);
	
	$option = '';
	foreach($lang as $key=>$value){
		$option .= '<option value="'.$key.'">'.$value.'</option>';
	}
	
	if(isset($_GET['mode'])) $selection = '<input name="mode" type="hidden" value="'.$_GET['mode'].'"/>';
	else $selection = '';
	$selection .= '
	<select name="lang" onchange="submit()">
		<option value="'.LANGUAGE.'">'.$lang[LANGUAGE].'</option>
		'.$option.'
	</select>
	';
	return $selection;
}

/// Render Step of Installation.
function step_render(){
	if(isset($_GET['mode']))$get_step = str_replace('step', '',$_GET['mode']);
	else $get_step = 0;
	$step_label = array(
		tt('License agreement'),
		tt('Setup validation'),
		tt('Permission validation'),
		tt('Root-Login information'),
		tt('Configuration'),
		tt('Happy Ending')
	);
	
	
	if(!isset($_SESSION['step'])) $_SESSION['step'] = 0;
	if($get_step > $_SESSION['step']) $_SESSION['step'] = $get_step;
	$step = $_SESSION['step'];
	
	$render = '<table><tr>';
	for($i=0; $i<=$step; $i++){
		if($i == $get_step){
			$render .= '
			<td align="center" valign="top" class="selected">
				<h1>'.$i.'</h1>'.$step_label[$i].'
			</td>';
		}else{
			$render .= '<td class="enable_step" align="center" valign="top">
				<a href="?mode=step'.$i.'"><h1>'.$i.'</h1>'.$step_label[$i].'
			</td>';
		}
	}
	
	for($i=$step+1; $i<=5; $i++){
		$render .= '<td class="unable_step" align="center" valign="top">
			<h1>'.$i.'</h1>'.$step_label[$i].'
		</td>';
	}
	$render .= '</tr></table>';
	return $render;
}

/// Get configuration value from serialized file.
/// @param $filename : name of serialized file.
function get_by_install($filename){
	$filename .= '.php';
	if(is_file($filename)){
		$handle = fopen ($filename, "r");
		flock($handle,LOCK_EX);
		$contents = fread($handle,filesize($filename));
		flock($handle,LOCK_UN);
		fclose ($handle);
		$contents = substr($contents,6,-3);
		return unserialize($contents);
	}
}

/// Check the existence of setup.php.
/// If setup.php does not exist, the constants are temporally defined.
function check_setup(){
	global $agree;
	if(isset($_GET['lang'])){
		define('LANGUAGE', $_GET['lang']);
		$_SESSION['lange'] = $_GET['lang'];
	}elseif(isset($_SESSION['lange'])){
		define('LANGUAGE', $_SESSION['lange']);
	}else{
		define('LANGUAGE', 'en');
	}
	
	if(is_file(dirname(__FILE__).'/../include/setup.php')){
		require_once('../include/setup.php');
		$agree = true;
	}else{
		$setup_file = dirname(dirname(__FILE__));
		define('DB_TYPE', 'mysql');
		define('ROOT_PATH', dirname(dirname(__FILE__)).'/');
		$root_uri = 'http://'.$_SERVER['HTTP_HOST'].dirname(dirname($_SERVER['PHP_SELF'])).'/';
		define('ROOT_URI', $root_uri);
		require_once('../include/include.inc');
		$message = sprintf('Please create file : %s', $setup_file.'/include/setup.php');
		$warn  = '<h3 style="color:red;">'.$message.'</h3>';
		$message = sprintf('You can use %s as example', $setup_file.'/include/setup.example.php');
		$warn .= '<h3 style="color:red;">'.$message.'</h3>';
		$message = 'You can not pass this step, before you create setup-file.';
		$warn .= '<h3 style="color:red;">'.$message.'</h3>';
		$agree = false;
		return $warn;
	}
}

/// Copy all files from a directory to target directory.
/// @param $dirIn : quell directory.
/// @param $dirOut : target directory.
function install_copy_all_files($dirIn,$dirOut){
	$d = dir($dirIn) or die('Invalid directory access :'.$dirIn);
	while (false !== ($entry = $d->read())) {
		if(substr($entry,0,1) != '.' and $entry != '..' and strlen($entry) and is_file($dirIn.'/'.$entry)){
			copy($dirIn.'/'.$entry, $dirOut.'/'.$entry)
			or die('Fail to copy file by copy_all_files() : '.$dirOut.$entry);
		}
	}
}

/// Step 0 of installation : License agreement and check existence of setup.php.
function step0(){
	global $agree;
	
	$handle = fopen('../LICENSE.txt', 'r');
	$license = fread ($handle, filesize ('../LICENSE.txt'));
	fclose($handle);
	
	$_render_ = '<h2>Step 0 : '.tt('License agreement').'</h2><pre>'.$license.'</pre>';
	if($agree){
		$_render_ .=  '
		<form action="index.php" method="get">
			<input type="hidden" name="mode" value="step1"/>
			<input type="submit" value="'.tt('I agree').'">
		</form>';
	}else{
		$_render_ .= '
		<form action="index.php" method="get">
			<input type="hidden" name="mode" value="step1"/>
			<input type="submit" value="I agree" disabled="disabled">
			<input type="button" value="'.tt('Try again').'" onclick="location.reload(true)">
		</form>';
	}
	
	return array('Step 0 : '.tt('License agreement'), $_render_);
}

/// Step 1 of installation : check constants in setup.php.
function step1(){
	$page = '<h2>Step 1 : '.tt('Setup validation').'</h2>';
	$page.= '<p>';
	$next_enable = '';
	$try = '';
	
	// Check database connection.
	if(DB_TYPE=='mysql')      list($next_enable_1, $result) = check_mysql();
	elseif(DB_TYPE=='pgsql')  list($next_enable_1, $result) = check_pgsql();
	elseif(DB_TYPE=='sqlite') list($next_enable_1, $result) = check_sqlite();
	else{
		$message = tt('Invalid DB_TYPE! X-BLC 0.3 supports only MySQL(mysql), PosgreSQL(pgsql), SQLite(sqlite).');
		$result .= '<b>DB_TYPE :</b> <b class="invalid">'.$message.'</b><br />';
		$next_enable = 'disabled="disabled"';
	}
	$page .= $result;
	
	/// Check ROOT_PATH
	list($next_enable_2, $result) = check_path();
	$page .= $result;
	
	/// Check ROOT_URI
	list($next_enable_3, $result) = check_uri();
	$page .= $result;
	
	/// Check DEFAULT_LANGUAGE
	list($next_enable_4, $result) = check_lang();
	$page .= $result;
	
	if(!($next_enable_1 and $next_enable_2 and $next_enable_3 and $next_enable_4)){
		$next_enable = 'disabled="disabled"';
		$try = '<input type="button" value="'.tt('Try again').'" onclick="location.reload(true)">';
		$messsage = tt('You have to edit <b>%s</b> to correct invalid constants.');
		$page.= '<p>'.sprintf($messsage, ROOT_PATH.'include/setup.php').'</p>';
	}
	
	$page.= '
	</p>
	<form action="index.php" method="get">
		<input type="hidden" name="mode" value="step2"/>
		<input type="button" value="'.tt('Back').'" onclick="back()">
		<input type="submit" value="'.tt('Next').'" '.$next_enable.'>
		'.$try.'
	</form>';
	
	return array('Step 1 : '.tt('Setup validation'), $page);
}

/// Check MySQL connection.
/// @return Result of connection checking.
function check_mysql(){
	$page = '<b>DB_TYPE :</b> <b class="valid">OK</b><br />';
	$invalid = tt('Invalid !!!');
	$result = array('<b>DB_HOST :</b> <b class="valid">OK</b><br />
	<b>DB_USER :</b> <b class="valid">OK</b><br />
	<b>DB_PASS :</b> <b class="valid">OK</b><br />', true);
	
	@ $dbh = mysql_pconnect(DB_HOST,DB_USER,DB_PASS) or 
	$result = array('<b>DB_HOST :</b> <b class="invalid">'.$invalid.'</b><br />
	<b>DB_USER :</b> <b class="invalid">'.$invalid.'</b><br />
	<b>DB_PASS :</b> <b class="invalid">'.$invalid.'</b><br />', false);
	$page = $result[0];
	$next_enable = $result[1];
	
	$result = array('<b>DB_NAME :</b> <b class="valid">OK</b><br />', true);
	@ mysql_select_db(DB_NAME,$dbh) or $result = array('
	<b>DB_NAME :</b> <b class="invalid">'.$invalid.'</b><br />', false);
	$page .= $result[0];
	$next_enable = $result[1];
	
	return array($next_enable, $page);
}

/// Check PostgreSQL connection.
/// @return Result of connection checking.
function check_pgsql(){
	$page .= '<b>DB_TYPE :</b> <b class="valid">OK</b><br />';
		
	$result = array('<b>DB_HOST :</b> <b class="valid">OK</b><br />
	<b>DB_USER :</b> <b class="valid">OK</b><br />
	<b>DB_PASS :</b> <b class="valid">OK</b><br />', true);
	
	@ $dbh = pg_connect('host='.DB_HOST.' user='.DB_USER.' password='.DB_PASS.' dbname='.DB_NAME) or
	$result = array('<b>DB_HOST :</b> <b class="invalid">Invalid !!!</b><br />
	<b>DB_USER :</b> <b class="invalid">Invalid !!!</b><br />
	<b>DB_PASS :</b> <b class="invalid">Invalid !!!</b><br />', false);
	$page .= $result[0];
	$next_enable = $result[1];
	
	return array($next_enable, $page);
}

/// Check SQLite connection.
/// @return Result of connection checking.
function check_sqlite(){
	$result = array('<b>DB_TYPE :</b> <b class="valid">OK</b><br />', true);
	
	@ $dbh = sqlite_open(ROOT_PATH.'files/sqlite.data', 0766, $sqliteerror) or
	$result = array(
		'<b>DB_TYPE :</b> <b class="invalid">Trouble with SQLite connection ('.$sqliteerror.'). You should change permission of '.ROOT_PATH.'files to 0757</b><br />',
		false
	);
	$page = $result[0];
	$next_enable = $result[1];
	return array($next_enable, $page);
}

/// Check ROOT_PATH.
/// @return Result of ROOT_PATH checking.
function check_path(){
	$valid_path = true;
	if(!file_exists(ROOT_PATH.'include/main.inc')) $valid_path = false;
	if($valid_path){
		$page ='<b>ROOT_PATH :</b> <b class="valid">OK</b><br />';
		$next_enable = true;
	}else{
		$root_path = dirname(dirname($_SERVER[SCRIPT_FILENAME]));
		$page ='<b>ROOT_PATH :</b> <b class="invalid">Invalid !!! Please try to use '.$root_path.'/</b><br />';
		$next_enable = false;
	}
	
	return array($next_enable, $page);
}

/// Check ROOT_URI.
/// @return Result of ROOT_URI checking.
function check_uri(){
	$uri = $_SERVER['HTTP_HOST'].dirname(dirname($_SERVER['PHP_SELF']));
	if(substr($uri,-1) == "/"){
		$uri = substr($uri,0,-1);
	}
	$root_uri = 'http://'.$uri.'/';
	if($root_uri == ROOT_URI){
		$page ='<b>ROOT_URI :</b> <b class="valid">OK</b><br />';
		$next_enable = true;
	}else{
		$root_uri2 = 'http://www.'.$uri.'/';
		if($root_uri == ROOT_URI){
			$page ='<b>ROOT_URI :</b> <b class="valid">OK</b><br />';
			$next_enable = true;
		}else{
			$page ='<b>ROOT_URI :</b> <b class="invalid">Invalid !!! Please try to use '.$root_uri.' or '.$root_uri2.'</b><br />';
			$next_enable = false;
		}
	}
	return array($next_enable, $page);
}

/// Check DEFAULT_LANGUAGE.
/// @return Result of DEFAULT_LANGUAGE checking.
function check_lang(){
	$default = DEFAULT_LANGUAGE;
	if(in_array($default, array('th', 'en'))){
		$page ='<b>DEFAULT_LANGUAGE :</b> <b class="valid">OK</b><br />';
		$next_enable = true;
	}else{
		$message = tt('Invalid !!! X-BLC 0.3 supports English(en) and Thai(th)');
		$page ='<b>DEFAULT_LANGUAGE :</b> <b class="invalid">'.$message.'</b>';
		$next_enable = false;
	}
	return array($next_enable, $page);
}

/// Step 2 of installation : check files and folders permissions.
function step2(){
	$title = 'Step 2 : '.tt('Permission validation');
	$page = '<h2>'.$title.'</h2>';
	$try = '';
	$path = array('files', 'section','xml');
	sort($path);
	$next_enable = '';
	foreach($path as $item){
		$item = ROOT_PATH.$item;
		if((fileperms($item) & 0x0002)){
			$page.='<b>'.$item.' :</b> <b class="valid">OK</b><br />';
		}
		else{
			$page.='<b>'.$item.' :</b> <b class="invalid">Invalid !!! Please change to 0757</b><br />';
			$next_enable = 'disabled="disabled"';
		}
	}
	
	$to_mkdir = array(
		'files/categories','files/member','files/user_logo','files/misc',
		'files/imageitem','files/equation','files/templates_c',
		'files/cache', 'files/config', 'files/themes', 'files/state',
		'files/config/blocks', 'files/config/cache',
		'files/config/config', 'files/config/feed', 'files/config/form',
		'files/config/items', 'files/config/menus', 'files/config/panels',
		'files/config/users','files/config/swapuser',
		'files/themes/custom/', 'files/themes/preview',
		'files/themes/default', 'files/themes/default/templates',
		'files/themes/default/css' , 'files/themes/default/image'
	);
	
	if($next_enable != 'disabled="disabled"'){
		foreach($to_mkdir as $item){
			if(!is_dir(ROOT_PATH.$item)) mkdir(ROOT_PATH.$item);
		}
		
		install_copy_all_files(ROOT_PATH.'files/default/themes', ROOT_PATH.'files/themes/default');
		install_copy_all_files(ROOT_PATH.'files/default/themes/templates', ROOT_PATH.'files/themes/default/templates');
		install_copy_all_files(ROOT_PATH.'files/default/themes/css', ROOT_PATH.'files/themes/default/css');
		install_copy_all_files(ROOT_PATH.'files/default/themes/image', ROOT_PATH.'files/themes/default/image');
		
		copy(ROOT_PATH.'files/xblc.png', ROOT_PATH.'files/misc/xblc.png');
		copy(ROOT_PATH.'files/default.png', ROOT_PATH.'files/user_logo/default.png');
	}
	
	if($next_enable == 'disabled="disabled"') $try = '<input type="button" value="'.tt('Try again').'" onclick="location.reload(true)">';
	$page.= '
	</p>
	<br />
	<form action="index.php" method="get">
		<input type="hidden" name="mode" value="step3"/>
		<input type="button" value="'.tt('Back').'" onclick="back()">
		<input type="submit" value="'.tt('Next').'" '.$next_enable.'>
		'.$try.'
	</form>';
	
	return array($title, $page);
}

/// Step 3 of installation : render form to get root-login information.
function step3(){
	$title = 'Step 3 : '.tt('Root-Login information');
	$page = '
	<script type="text/javascript" src="'.ROOT_URI.'include/jslib/formcheck.js"></script>
	<script type="text/javascript" src="'.ROOT_URI.'include/jslib/sha1.js"></script>
	<script type="text/javascript">
		var select_from = new Array();
		var not_null = new Array("login_name","prepassword","confirm_password");
		var describe = new Array();
		describe["login_name"] = "'.tt('login name').'";
		describe["email"] = "'.tt('email').'";
		describe["prepassword"] = "'.tt('password').'";
		describe["confirm_password"] = "'.tt('confirm password').'";
		
		var please_fill ="'.tt('Please insert data in : ').'";
		var passwd_confirmed ="'.tt('Password and confirmation must be the same.').'";
		var passwd_not_changed ="'.tt('Password is shorter than 8 characters. It is not changed.').'";
		var passwd_to_short ="'.tt('Password is to short. It must be longer than 8 characters.').'";
		var agt=navigator.userAgent.toLowerCase();
		
		function sz(t) {
			a = t.value.split("\n");
			if(a.length < 25 && a.length >5) t.rows = a.length;
			else if(a.length > 25) t.rows = 25;
		}
		
	</script>

	<div class="form">
	<a name="edit"></a>
	<form enctype="multipart/form-data" method="post" action="index.php?mode=step4"
	name="xblcform" onsubmit="return formCheck()">
	<h2>'.$title.'</h2>
		<p>
		'.tt('<b>Important</b> : Please, remember this information for root\'s loging-in. Root is the person, who can access and manage everything in system.').'
		</p>
		<label>'.tt('login name').'</label>
		<input name="login_name" value="" size="40" />
		<label>'.tt('email').'</label>
		<input name="email" value="" size="40" />
		<label>'.tt('password').'</label>
		<input name="prepassword" value="" size="40" type="password"/>
		<label>'.tt('confirm password').'</label>
		<input name="confirm_password" value="" size="40" type="password"/>
		<input name="password" value="" type="hidden"/>
		<input name="section" value="1" type="hidden"/>
		<br /><br />
		<input type="button" value="'.tt('Back').'" onclick="back()" style="display:inline;">
		<input type="submit" value="'.tt('Next').'" style="display:inline;"/>
	</form></div>';
	return array($title, $page);
}

/// Step 4 of installation : initial system and get minimal configuration.
function step4(){
	$title = 'Step 4 : '.tt('Configuration');
	if(strlen($_POST['login_name'].$_POST['password'].$_POST['email'])){
		$_SESSION['login_salt'] = generate_key(32);
		$_SESSION['login_crypt'] = sha1($_POST['password'].$_SESSION['login_salt']);
		$_SESSION['login_name'] = $_POST['login_name'];
		$_SESSION['login_group'] = array(1);
		$_SESSION['authority'] = "ok";
		$_SESSION['xblc_section'] = 1;
		$_SESSION['xblc_id'] = 1;
		if(!db_table_exist('users')){
			create_db_tables();
			init_section();
			init_user();
		}else{
			update_user();
		}
	}
	if(!defined('SECTION')) define('SECTION', 1);
	xblc_auth(array(), array(), true);
	$page  = '<h2>'.$title.'</h2>';
	$page .= config_page();
	return array($title, $page);
}

/// Create tables in database.
function create_db_tables(){
	$filename = ROOT_PATH.'include/database/create_table_'.DB_TYPE.'.sql';
	$handle = fopen ($filename, "r");
	flock($handle,LOCK_EX);
	$contents = fread($handle,filesize($filename));
	flock($handle,LOCK_UN);
	fclose ($handle);
	$sqls = split(';',$contents);
	foreach($sqls as $sql){
		db_query($sql, true);
	}
}

/// Initial the first section.
function init_section(){
	require_once(ROOT_PATH.'files/default/config/config.inc');
	require_once(ROOT_PATH.'files/default/config/cache.inc');
	require_once(ROOT_PATH.'include/load.module.inc');
	
	define('SECTION', 1);
	
	// Insert into database.
	db_query("INSERT INTO section(name) VALUES('My Site')");
	
	// Make directory
	$dir = ROOT_PATH.'files/cache/1';
	if(!is_dir($dir)) @ mkdir($dir) or null;
	$dir = ROOT_PATH.'files/config/panels/1';
	if(!is_dir($dir)) @ mkdir($dir) or null;
	
	// Serialize default configurations.
	$config_default = config_default();
	$config_default['section'] = 1;
	$config_default['section_name'] = 'My Site';
	$config_default['section_path'] = '';
	$config_default['start'] = date('Y-m-d');
	
	pickle($config_default, 'files/config/config/config1.inc');
	pickle(cache_default(), 'files/config/cache/cache1.inc');
	pickle(default_panel(), 'files/config/config/panel1.inc');
	pickle(default_access(), 'files/config/config/access1.inc');
	pickle(array(), 'files/config/blocks/block1.inc');
	pickle(array(), 'files/config/menus/menu1.inc');
	pickle(array(), 'files/config/items/items1.inc');
	pickle(array(), 'files/config/items/imageitems1.inc');
	pickle(array(), 'files/config/items/moduleitems1.inc');
	pickle(array(), 'files/config/items/moduleitemgroups1.inc');
	pickle(array(), 'files/config/feed/feed1.inc');
}

/// Initial the first user.
function init_user(){
	// Insert user into database.
	if(count(db_array('SELECT id FROM users LIMIT 1')) == 0){
		$q  = "INSERT INTO users(login_name, password, logo, email, section, space_used)";
		$q .= "VALUES('%s', '%s', 'files/default.png', '%s', 1, 0)";
		$q  = sprintf($q, $_POST['login_name'], $_POST['password'], $_POST['email']);
		db_query($q);
	}
	// Set default config.
	require_once(ROOT_PATH.'include/user.info.inc');
	pickle(default_user_config(),'files/config/users/user1.inc');
	
	// Make personal directory.
	$user_dir = ROOT_PATH.'files/member/1';
	if(!is_dir($user_dir)) mkdir($user_dir);
	
}

/// Update user information (by resend user information)
function update_user(){
	// Insert user into database.
	if(count(db_array('SELECT id FROM users LIMIT 1')) == 0){
		$q = "UPDATE users SET login_name='%s', password='%s', email='%s' WHERE id=1";
		$q = sprintf($q, $_POST['login_name'], $_POST['password'], $_POST['email']);
		db_query($q);
	}
}

/// Render form for minimal section configuration.
/// @return Form for minimal section configuration.
function config_page(){
	$preconf = preconfig();
	$preradio = '';
	$i = 0;
	foreach($preconf as $key => $value){
		if($i==0) $check = 'checked="checked"';
		else $check = '';
		$preradio .= '<input type="radio" name="preconfig" value="'.$key.'" '.$check.'/> '.$value['label'];
		$preradio .= '<p class="help_text">'.$value['description'].'</p>';
		$i++;
	}
	$page = '
	<form enctype="multipart/form-data" method="post" action="index.php?mode=step5" name="xblcform">
		<label>'.tt('section name').'</label>
		<input name="section_name" value="" size="40" />
		<label>'.tt('section description').'</label>
		<input name="section_slogan" value="" size="40" />
		<label>'.tt('section pre-configuration').'</label>
		'.$preradio .'
		<br />
		<input type="button" value="'.tt('Back').'" onclick="back()" style="display:inline;">
		<input type="submit" value="'.tt('Next').'" style="display:inline;"/>
	</form>';
	return $page;
}

/// Get information array of system-preconfiguration.
/// @return Information array of system-preconfiguration.
function preconfig(){
	$preconfig = array(
		'personal' => array(
			'label' => tt('Personal Website'),
			'description' => tt('This pre-configuration allows you to create your personal website with blogging system and image gallery.'),
		),
		'blog' => array(
			'label' => tt('Blogging system'),
			'description' => tt('Minimal configuration with blog module. Blogging system allows you to easily publish your opinion in internet.'),
		),
		'community' => array(
			'label' => tt('Community Website'),
			'description' => tt('With community pre-configuration, your website initially contains forum, news, mailing-list and FAQ system.'),
		),
		'document' => array(
			'label' => tt('Document Center'),
			'description' => tt('Document Center provides document creation and management system. The documents have chapters structure and can be internationalized.'),
		),
		'sme' => array(
			'label' => tt('SME Website'),
			'description' => tt('Website for Small and Medium Enterprise or other institution, which want to provide news and information about themselves.'),
		),
		/* In planning
		'magazin' => array(
			'label' => tt('Online Magazin'),
			'description' => tt(''),
		),
		'portal' => array(
			'label' => tt('Web Portal'),
			'description' => tt(''),
		),
		'enterprise' => array(
			'label' => tt('Enterprise Website'),
			'description' => tt(''),
		),
		'shop' => array(
			'label' => tt('Online Shop'),
			'description' => tt(''),
		),
		'social' => array(
			'label' => tt('Social Network'),
			'description' => tt(''),
		),
		'knowledge' => array(
			'label' => tt('Knowledge Management System'),
			'description' => tt(''),
		),
		'wiki' => array(
			'label' => tt('Wiki-Based Knowledge Management'),
			'description' => tt(''),
		),
		'bookmark' => array(
			'label' => tt('Social Bookmarking'),
			'description' => tt(''),
		),
		*/
	);
	ksort($preconfig);
	return $preconfig;
}

/// Render finishing message with minimal text-guideline.
function finish_message(){
	$m = tt('%sHome Page%s of your website can be found here.');
	$item  = '<li>'.sprintf($m, '<a href="'.ROOT_URI.'"><b>', '</b></a>').'</li>';
	$m = tt('With %sAdmin Page%s, you can manage everthing on your website.');
	$item .= '<li>'.sprintf($m, '<a href="'.ROOT_URI.'admin"><b>', '</b></a>').'</li>';
	$m = tt('Now you can configurate your system on %sSection-Configuration%s.');
	$item .= '<li>'.sprintf($m, '<a href="'.ROOT_URI.'admin/?/config_page"><b>', '</b></a>').'</li>';
	$m = tt('If you want to extend your system with modules, you can go to %sLoad-Module%s to activate modules.');
	$item .= '<li>'.sprintf($m, '<a href="'.ROOT_URI.'admin/?/load_module"><b>', '</b></a>').'</li>';
	$m = tt('You can use %sTheme Manage%s to customize looks and feels of your site.').'</li>';
	$item .= '<li>'.sprintf($m, '<a href="'.ROOT_URI.'admin/?/select_themes"><b>', '</b></a>');
	$remove   = tt('After this step, please remove directory "install" for security of your website.');
	$thank    = tt('Have fun, %sX-BLC Team%s');
	$thank    = sprintf($thank, '<a href="http://www.biolawcom.de/xblc/">', '</a>');
	$message  = '<ul>'.$item.'</ul>';
	$message .= '<p style="color:red;">'.$remove.'</p>';
	$message .= '<p>'.$thank.'</p>';
	return $message;
}

/// Step 5 of installation : save configuration and run pre-configuration script.
function step5(){
	define('SECTION', 1);
	define('USER_ID', 1);
	define('Q', '?/');
	define('SECTION_URI', ROOT_URI);
	define('NOW', date('Y-m-d H:i:s'));
	define('TODAY', date('Y-m-d'));
	if(strlen($_POST['section_name'].$_POST['section_slogan'])){
		require_once(ROOT_PATH.'include/config.tools.inc');
		require_once(ROOT_PATH.'include/load.module.inc');
		require_once(ROOT_PATH.'include/form.tools.inc');
		require_once('preconfig.inc');
		
		db_query("UPDATE section SET name='$_POST[section_name]' WHERE id=1");
		set_config('section_name', $_POST['section_name']);
		set_config('slogan', $_POST['section_slogan']);
		save_config();
		$func = 'install_init_'.$_POST['preconfig'];
		$func();
	}
	$title = tt('Happy Ending').' : '.tt('X-BLC has been successfully installed');
	$page  = '<h2>'.$title.'</h2>';
	$page .= finish_message();
	write_file(ROOT_PATH.'/files/state/install', "");
	mkdir(ROOT_PATH.'/files/state/1/');
	write_file(ROOT_PATH.'/files/state/1/product', "");
	return array(tt('Happy Ending'), $page);
}

?>

