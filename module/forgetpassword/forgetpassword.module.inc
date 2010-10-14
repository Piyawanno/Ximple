<?php
forgetpassword_switch();

function forgetpassword_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'reset'){
		execute_add_class('forgetpassword', 'ResetPassword');
		include('ResetPassword.class.inc');
	}else{
		execute_add_class('forgetpassword', 'ForgetPassword');
		include('ForgetPassword.class.inc');
	}
}
?>
