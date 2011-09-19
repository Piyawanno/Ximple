<?php
execute_add_function('dbbackup');
execute_add_function('dbbackup_config');
execute_add_function('dbbackup_config_save');

function dbbackup(){
	if(cron_check_process()){
		require_once(INCLUDE_PATH.'tool/dump.tool.inc');
		dump();
	}
}

function dbbackup_config($params, $result){
	$cron = cc('cron');
	$interval = Model::timeInterval(tt('backup interval'));
	$interval->isMinute = false;
	$interval->isSecond = false;
	$result[tt('Database Backup')] = array(
		'dbbackup_interval' => $interval,
	);
	return $result;
}

function dbbackup_config_save(){
	$cron = cc('cron');
	$cron['dbbackup'] = pp('dbbackup_interval');
	config_set('cron', $cron);
	config_set('dbbackup_interval', pp('dbbackup_interval'));
}
?>
