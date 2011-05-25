<?php
require_once(ROOT_PATH.'include/class/column/HiddenColumn.class.inc');

class UserLoginHashColumn extends HiddenColumn{
	function UserLoginHashColumn(){
		HiddenColumn::HiddenColumn('', 'char');
	}
	
	function triggerPostInsert(){
		$this->data = sha1($this->data);
	}
}
?>
