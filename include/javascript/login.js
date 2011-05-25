function encryptPasswd(){
	if($('#user_password').val().length == 0 && !insertUser){
		alert(passwdNotChange);
	}
	if($('#user_password').val() == $('#user_confirm_password').val()){
		var passwd = $('#user_password').val();
		if(passwd.length){
			$('#user_password').val(hex_sha1(passwd));
			$('#user_confirm_password').val('');
		}
		$('#user_login_name_hash').val($('#user_login_name').val());
	}
}
