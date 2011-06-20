<?php
/// @file
/// This file provides function for bootstrap of XimpleCMS.

/// @author Kittipong Piyawanno <k.piyawanno@gmail.com>

/// Bootstrap of XimpleCMS.
function boot(){
	session_start();
	require('precache.tool.inc');
	$to_die = precache_get_page();
	if(!$to_die){
		if(isset($_POST['logout']) and $_POST['logout'] == 'logout'){
			session_destroy();
		}
		require('setini.tool.inc');
		setini();
		require('main.tool.inc');
		main_init();
		main_exec();
	}
}
?>
