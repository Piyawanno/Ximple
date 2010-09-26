<?php
class OwnerColumn extends ModelColumn{
	function OwnerColumn(){
		$this->type = 'int';
		$this->form = 'hidden';
		$this->defaultData = USER_ID;
		$this->data = USER_ID;
	}
	
	public function triggerSelect(){
		if($this->data != -1){
			$column =  array('id', 'login_name', 'email', 'avatar', 'space_used');
			$data = db_select('users', $column, 'WHERE id='.$this->data);
			$this->data = $data[$this->data];
		}else{
			$this->data = array(
				'id' => -1,
				'avatar' => 'files/avatar/default.png',
			);
		}
	}
}
?>
