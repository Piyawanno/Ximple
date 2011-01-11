<?
execute_add_function('login');

function login(){
	login_clear_session();
	document_set_title(tt('Login'));
	document_set_path(tt('Login'));
	return login_render();
}

function login_clear_session(){
	if(!authority_is_guest()){
		authority_clear_session();
	}
}

function login_render(){
	$render_array = array(
		'forget_password' => cc('forget_password'),
		'registable' => cc('registable')
	);
	head_add_css('form.css');
	head_add_js('include/external/sha1.js');
	return render($render_array, 'loginpage.tpl', 'loginpage');
}

?>
