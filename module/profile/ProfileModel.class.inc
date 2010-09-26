<?php
class ProfileModel extends Model{
	function ProfileModel(){
		$this->owner = $this->hidden(USER_ID, 'int');
		$this->profiletype = new ProfileTypeColumn();
		$this->profile = $this->shortText(tt('profile'));
	}
}

class ProfileTypeColumn extends ModelColumn{
	function ProfileTypeColumn(){
		$this->type = 'int';
		$this->form = 'select';
		$this->label = tt('profile type');
		$this->selection = array();
	}
	
	public function triggerInsertForm(){
		$this->getSelect();
	}
	
	public function triggerUpdateForm(){
		$this->getSelect();
	}
	
	public function triggerSelect(){
		$data = db_select_single_column('profiletype', 'name', 'WHERE id='.(int)$this->data);
		$this->data = $data[$this->data];
	}
	
	private function getSelect(){
		$this->selection = db_select_single_column('profiletype', 'name', 'WHERE section='.SECTION);
	}
	
}
?>
