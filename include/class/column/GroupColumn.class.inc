<?php
require_once('CheckBoxColumn.class.inc');
class GroupColumn extends CheckBoxColumn{
	public $isExceptedAdmin = true;
	public $isExceptedGuest = false;
	public $isExceptedUser  = false;
	
	function GroupColumn($label, $help=null){
		CheckBoxColumn::CheckBoxColumn($label, $help),
		$this->defaultData = array(2);
		$this->data = array(2);
	}
	
	public function triggerInsertForm(){
		$this->getOption();
	}
	
	public function triggerUpdateForm(){
		$this->getOption();
	}
	
	public function triggerPostInsert(){
		$this->data = serialize($this->data);
	}
	
	public function triggerPostUpdate(){
		$this->data = serialize($this->data);
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
