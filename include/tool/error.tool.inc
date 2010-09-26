<?php

function error_fatal($title, $message){
	header('HTTP/1.1 500 Internal Server Error');
	$data = array(
		'title' => $title,
		'message' => $message
	);
	echo(render($data, 'error.tpl', 'error_fatal'));
	if(function_exists('io_write_log')) io_write_log($message, 'fatal');
	if(function_exists('db_rollback')) db_rollback();
	die();
}

function error_syslog($message, $redirect=null){
	header('HTTP/1.1 500 Internal Server Error');
	
	if($redirect) $uri = SECTION_URI.Q.$redirect;
	else $uri = SECTION_URI;
	
	$message .= sprintf(tt('<p>You should go to <a href="%s">this page</a> for further action.</p>'), $uri);
	$data = array(
		'title' => tt('System error occurred'),
		'message' => $message
	);
	db_rollback();
	io_write_log($message, 'system');
	echo(render($data, 'error.tpl', 'error_syslog'));
	die();
}

function error_denied(){
	header('HTTP/1.1 402 Access Denied');
	$uri = SECTION_URI;
	$message  = tt('Invalid access for called page.');
	$message .= sprintf(tt('<p>You should go to <a href="%s">this page</a> for further action.</p>'), $uri);
	$data = array(
		'title' => tt('System error occurred'),
		'message' => $message
	);
	db_rollback();
	io_write_log(tt('Invalid access for called page.'), 'denied');
	echo(render($data, 'error.tpl', 'error_syslog'));
	die();
}

function error_db_log($query, $error){
	$message = 'Database error : '.$error.' by query : '.$query.' ';
	if(!state_is_product()){
		error_syslog($message);
	}else{
		db_rollback();
		io_write_log($message, 'system');
		die();
	}
}

function error_db_connect(){
	$message = 'Ximple can not connect to database, please check your database setup.';
	if(!state_is_product()){
		error_fatal('DB Connection Error', $message);
	}else{
		io_write_log($message, 'db_connect');
		die();
	}
}

function error_not_found(){
	header("HTTP/1.0 404 Not Found");
	$message = 'The requested page can not be found on the server.';
	$data = array(
		'title' => 'Page not found',
		'message' => $message,
	);
	echo(render($data, 'error.tpl', 'error_not_found'));
	db_rollback();
	io_write_log($message, 'not_found');
	die();
}

?>
