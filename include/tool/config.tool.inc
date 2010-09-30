<?php

function config_change($key, $value){
	$GLOBALS['tmp_config'][$key] = $value;
}

function config_set($key, $value){
	$GLOBALS['config'][$key] = $value;
}

function config_append($key, $value){
	$GLOBALS['config'][$key][] = $value;
}

function config_append_assc($name, $key, $value){
	$GLOBALS['config'][$name][$key] = $value;
}

function config_drop($key){
	unset($GLOBALS['config'][$key]);
}

function config_drop_by_value($key, $value){
	if(isset($GLOBALS['config'][$key]) and is_array($GLOBALS['config'][$key])){
		$conf = $GLOBALS['config'][$key];
		foreach($conf as $index => $set_value){	
			if($set_value == $value){
				unset($GLOBALS['config'][$key][$index]);
			}
		}
	}
}

function config_drop_assc($name, $key){
	unset($GLOBALS['config'][$name][$key]);
}

function config_save(){
	$config_dir = ROOT_PATH.'files/config/';
	if(!is_dir($config_dir)) mkdir($config_dir);
	io_serialize($GLOBALS['config'], $config_dir.'config'.SECTION);
	cache_clear_section();
}

function config_default_require(){
	return array(
		'block' => 'Block.class.inc',
		'menu' => 'Menu.class.inc',
		'module' => 'module.module.inc',
		'file' => 'file.module.inc',
		'shortnote' => 'ShortNote.class.inc',
		'message' => 'Message.class.inc',
		'captcha' => 'captcha.module.inc',
		'about' => 'About.class.inc',
		'config' => 'SectionConfig.class.inc',
		'theme' => 'theme.module.inc',
		'user' => 'User.class.inc',
		'group' => 'group.module.inc',
		'profiletype' => 'ProfileType.class.inc',
		'profile' => 'Profile.class.inc',
		'registration' => 'registration.module.inc',
		'account' => 'account.module.inc',
		'section' => 'Section.class.inc',
		'syslog' => 'syslog.module.inc',
		'category' => 'Category.class.inc',
		'comment' => 'Comment.class.inc',
		'freetag' => 'freetag.module.inc',
		'tracker' => 'tracker.module.inc',
		'flashblock' => 'flashblock.module.inc',
		'imageloader' => 'imageloader.module.inc',
		'search' => 'search.module.inc',
	);
}

function config_default_module_name(){
	return array(
		'about' => 'About Us',
	);
}


/// Get default panel array.
/// @return Default panel array.
function config_default_panel(){
	return array(
		'::: My Account :::' => array(
			'my files' => 'file_manage_user',
			'my message' => 'message',
			'my profile' => 'profile',
			'my short note' => 'shortnote',
			'my tracker' => 'tracker',
			'configure account' => 'account'
		),
		'Comments' => array( 
			'my comments' => 'comment_list',
			'on my contribution' => 'comment_contributor_list',
			'in section' => 'comment_section_list',
		)
	);
}

/// Get array of default panel access role.
/// @return Array of default panel access role.
function config_default_panel_access(){
	$panel = array(
		'Block & Menu' => array(  
			'block_admin' => array(  
				'block' => 'block',
			),
			'menu_admin' => array(  
				'menu' => 'menu'
			),
		),
		'Users & Groups' => array(  
			'user_admin' => array(  
				'user' => 'user',
				'registration' => 'registration_config',
			),
			'group_admin' => array(  
				'group & role' => 'group'
			),
			'profile_admin' => array(  
				'profile type' => 'profiletype'
			)
		),
		'System Admin' => array(  
			'file_admin' => array(  
				'manage file' => 'file_manage_admin'
			),
			'module_admin' => array(  
				'manage module' => 'module_manage'
			),
			'config_admin' => array(  
				'configure section' => 'config',
			),
			'syslog_admin' => array(  
				'system log' => 'syslog_render'
			),
		),
		'Themes' => array(  
			'theme_admin' => array(  
				'select themes' => 'theme_select',
				'configure theme' => 'theme_config',
				'custom css' => 'theme_css',
				'custom image' => 'theme_image'
			)
		),
	);
	if(SECTION == 1){
		$panel['System Admin']['section_admin']['add section'] = 'section';
	}
	return $panel;
}

/// Get array of default access description.
/// @return array of default access description.
function config_default_role(){
	$default = array(
		'user_admin' => array(
			'name' => 'User Manager',
			'description' => 'Who can manage users in Section.'),
		'comment_admin' => array(
			'name' => 'Comment Manager',
			'description' => 'Who can delete and edit all comments in Section.'),
		'group_admin' => array(  
			'name' => 'Group Manager',
			'description' => 'Who can manage groups and roles in Section.'),
		'file_admin' => array(  
			'name' => 'File Manager',
			'description' => 'Who can manage System-Files in Section'),
		'profile_admin' => array(  
			'name' => 'Profiler',
			'description' => 'Who can manager Profile-Type and User-Profile of all users in Section'),
		'module_admin' => array(  
			'name' => 'Module Loader',
			'description' => 'Who can manage modules in Section.'),
		'theme_admin' => array(  
			'name' => 'Designer',
			'description' => 'Who can select and configure theme in Section.'),
		'config_admin' => array(  
			'name' => 'Configurator',
			'description' => 'Who can configure important parameter of Section.'),
		'section_admin' => array(  
			'name' => 'Section Manager',
			'description' => 'Who can add and delete Sections.'),
		'block_admin' => array(  
			'name' => 'Block Manager',
			'description' => 'Who can manage Blocks in Section.'),
		'menu_admin' => array(  
			'name' => 'Menu Manager',
			'description' => 'Who can manage Menus in Section.'),
		'syslog_admin' => array(  
			'name' => 'System Watcher',
			'description' => 'Who can access Syslog-management in Section.')
	);
	return $default;
}

function config_default(){
	return array(  
		'theme' => 'bluesky',
		'icon' => 'files/misc/ximple.png',
		'section_name' => 'My Website',
		'section_slogan' => '',
		'section_path' => '',
		'section_description' => '',
		'lang' => 'en',
		'home_label' => 'Home',
		'default_user_logo' => 'files/userlogo/default.png',
		'notify_interval' => 30,
		'index_mode' => 'about',
		'start' => '2006-09-19',
		'meta_data' => '',
		'allowed_tags' => '<a><p><img><strong><h3><h4><h5><obj><param><embed><span><em><blockquote><table><tbody><tr><td><ul><ol><li><br>',
		'cachable_mode' => array( ),
		'cache_mode' => 'txt',
		'cache_time' => '18000',
		'increase_read' => array( ),
		'feed_mode' => array( ),
		'feed_available_mode' => array( ),
		'feed_number' => '10',
		'feed_comment' => '',
		'feed_type' => array (
			0 => 'atom',
			1 => 'rss',
		),
		'feed_number' => '10',
		'feed_comment' => 1,
		'feed_comment_explicit' => 0,
		'antispam_salt' => (string) md5(rand()),
		'antispam_time' => 21600,
		'block_position' => array(
			'left' => 'Left Sidebar',
			'foot' => 'Foot',
			'disabled' => 'Disabled',
		),
		'block_primary_position' => 'left',
		'menu_include_block' => true,
		'navigation' => array(
			'home' => 'Home',
			'about' => 'About',
		),
		'navigation_enabled' => array('home', 'about'),
		'module_require' => array(),
		'module_name' => array(),
		'syslog_enable' => true,
		'syslog_time' => 604800,
		'tracker_enable' => true,
		'tracker_time' => 604800,
		'time_zone' => 'UTC',
	);
}

function config_check_default($config){
	$default = config_default();
	foreach($default as $key=>$value){
		if(!isset($config[$key])){
			$config[$key] = $value;
		}
	}
	$config['module_require'] = array_merge($config['module_require'], config_default_require());
	$config['module_name'] = array_merge($config['module_name'], config_default_module_name());
	if(!is_dir(ROOT_PATH.'theme/'.$config['theme'])){
		$config['theme'] = 'default';
	}
	return $config;
}
?>
