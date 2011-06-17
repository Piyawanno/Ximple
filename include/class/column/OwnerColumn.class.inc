<?php
require_once('HiddenColumn.class.inc');
class OwnerColumn extends HiddenColumn{
	function OwnerColumn(){
		HiddenColumn::HiddenColumn(USER_ID, 'int');
	}
	
	public function triggerSelect(){
		if($this->data != -1){
			$column =  array('id', 'login_name', 'email', 'avatar', 'space_used');
			$data = db_select('users', $column, 'WHERE id='.$this->data);
			$uid = $this->data;
			$this->data = $data[$uid];
			$this->data['config'] = io_unserialize(FILES_PATH.'account/'.$uid);
		}else{
			$this->data = array(
				'id' => -1,
				'avatar' => 'files/avatar/default.png',
			);
		}
	}
}
?>
