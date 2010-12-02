<?php
include_once(ROOT_PATH.'include/class/FileSizeColumn.class.inc');

class UserModel extends Model{
	function UserModel(){
		$this->login_name = new UserLoginName();
		$this->login_name->listMode = 'profile';
		$this->email = $this->email(tt('email'), tt('Email must be unique.'));
		$this->email->isList = true;
		$this->email->isReachable = true;
		$this->password = new UserPassword();
		$this->confirm_password = $this->password(tt('confirm password'));
		$this->confirm_password->isDB = false;
		$this->status = $this->hidden('active');
		$this->avatar = $this->image(tt('avarta'), 'files/avatar/', 120);
		$this->section = $this->section();
		$this->space_used = new FileSizeColumn(tt('used space'));
		$this->login_name_hash = new UserLoginHash();
	}
}

class UserLoginHash extends ModelColumn{
	function UserLoginHash(){
		$this->type = 'char';
		$this->form = 'hidden';
	}
	
	function triggerPostInsert(){
		$this->data = sha1($this->data);
	}
}

class UserLoginName extends ModelColumn{
	function UserLoginName(){
		$this->form = 'char';
		$this->type = 'char';
		$this->isList = true;
		$this->isReachable = true;
		$this->isNotNull = true;
		$this->label = tt('login name');
		$this->help = tt('Login name must be longer than 4 characters and unique.');
	}
} 

class UserPassword extends ModelColumn{
	function UserPassword(){
		$this->form = 'password';
		$this->type = 'char';
		$this->label = tt('password');
	}
	
	function triggerInsertForm(){
		$this->help = tt('Password must be longer than 8 characters');
		$this->isNotNull = true;
	}
	
	function triggerUpdateForm(){
		$this->help = tt('If empty, password will not be changed.');
		$this->help.= tt('Else, password must be longer than 8 characters');
		$this->data = '';
		$this->isNotNull = false;
	}
	
	function triggerPreUpdate(){
		$this->isDB = strlen(pp('password')) > 0;
	}
}
?>
