<?php
class GroupColumn extends ModelColumn{
	public $isExceptedAdmin = true;
	public $isExceptedGuest = false;
	public $isExceptedUser  = false;
	
	function GroupColumn($label, $help=null){
		$this->type = 'array';
		$this->form = 'checkbox';
		$this->label = $label;
		$this->help = $help;
		$this->defaultData = array(2);
		$this->data = array(2);
		$this->isSerialize = true;
	}
	
	public function triggerInsertForm(){
		$this->getOption();
	}
	
	public function triggerUpdateForm(){
		$this->getOption();
	}
	
	private function getOption(){
		$excepted = '';
		if($this->isExceptedAdmin) $excepted .= ' AND id!=1 ';
		if($this->isExceptedGuest) $excepted .= ' AND id!=2 ';
		if($this->isExceptedUser)  $excepted .= ' AND id!=3 ';
		$clause = 'WHERE ((section='.SECTION.' OR id <=3) '.$excepted.')';
		$this->option = db_select_single_column('groups', 'name', $clause);
	}
}
?>
