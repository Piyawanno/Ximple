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
		$this->option = array();
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
		$column = array('id', 'name', 'allowed_group');
		$allType = db_select('profiletype', $column, 'WHERE section='.SECTION);
		$this->option = array();
		foreach($allType as $key => $value){
			$groups = unserialize($value['allowed_group']);
			if(authority_check_users_groups(array(), $groups)){
				$this->option[$value['id']] = $value['name'];
			}
		}
	}
	
}
?>
