<?php
class PeopleDataModel extends Model{
	public $moduleName = 'peopleinfo';
	public $tableName = 'people_data';
	public $dropMode = 'peopleinfo_drop_data';
	
	function PeopleDataModel($peopleID=null){
		$type = cc('peopleinfo_data_type');
		$this->data_type = $this->select(tt('data type'), $type);
		$this->data = $this->title(tt('data'));
		$this->people = $this->none($peopleID, 'int');
		$this->people->isGridForm = false;
		$this->people->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->people->data = $parentID;
	}
}
?>
