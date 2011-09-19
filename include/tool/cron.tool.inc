<?php
function cron_init(){
	define('XIMPLE_CMS', 'initialized');
	init_get_setup();
	init_set_path();
	init_include();
	init_config();
	db_init();
	init_set_time_zone();
	init_var();
	init_check_cron();
	authority();
	translate_define_language();
	config_translate();
	translate_add_directory(THEME_PATH.''.cc('theme'));
}

function cron_exec(){
	$cron = cc('cron');
	$message = "XimpleCMS running Cron-Jobs\n";
	ob_start();
	if(is_array($cron) and count($cron)){
		$time = time();
		foreach($cron as $key => $value){
			if($time%$value == 0){
				execute($key);
				$message .= sprintf("Execute %s @ %s.\n", $key, date('Y-m-d H:i:s', $time));
			}
		}
		cron_write_log($time, $message);
		echo("$time\n$message");
		ob_flush();
		flush();
	}
	sleep(1);
	if(init_get_cron_time() != time()) init_start_new_cron();
	else echo("Double Crons detected. Cron-Loop stopped.");
}

function cron_write_log($time, $message){
	$dir = FILES_PATH.'cron/';
	if(!is_dir($dir)) mkdir($dir);
	io_write_file($dir.SECTION.'.txt', (string) $time);
	io_append_file($dir.SECTION.'_log.txt', "$time\n$message");
}
?>
