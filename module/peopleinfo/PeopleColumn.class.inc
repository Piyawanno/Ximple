<?php
require_once(INCLUDE_PATH.'class/column/HiddenColumn.class.inc');

class PeopleColumn extends HiddenColumn{
	function PeopleColumn(){
		HiddenColumn::HiddenColumn(0, 'int');
	}
	
	function triggerPostInsert(){
		$userData = array(
			'login_name' => pp('name')
		);
		$this->data = db_insert('users', $userData);
		$this->insertGroup();
	}
	
	function triggerPostUpdate(){
		$userData = array(
			'login_name' => pp('name'),
		);
		db_update('users', $userData, $this->data);
		$this->insertGroup();
	}
	
	private function insertGroup(){
		$groups = cc('peopleinfo_related');
		if(count($groups)){
			foreach($groups as $key => $value){
				$clause = 'users='.((int) $this->data).' AND groups='.$value;
				db_drop_many('map', $clause);
				$data = array(
					'users' => $this->data,
					'groups' => $value,
					'section' => SECTION,
				);
				db_insert('map', $data);
			}
		}
	}
}
?>
