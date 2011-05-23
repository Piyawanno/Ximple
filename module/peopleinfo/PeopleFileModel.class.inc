<?php
class PeopleFileModel extends Model{
	public $moduleName = 'peopleinfo';
	public $tableName = 'people_file';
	public $dropMode = 'peopleinfo_info_drop_people_file';
	
	function PeopleFileModel($informationID=null){
		$this->short_description = $this->title(tt('short description'));
		$this->file = $this->file('file', 'files/peopleinfo/');
		$this->type = $this->none('', 'char');
		$this->type->isGridForm = false;
		$this->type->type = 'array';
		$this->information = $this->none($informationID, 'int');
		$this->information->isGridForm = false;
		$this->information->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->information->defaultData = $parentID;
	}
	
	public function triggerPreInsert(){
		$this->getType();
	}
	
	public function triggerPreUpdate(){
		$this->getType();
	}
	
	private function getType(){
		$this->type->defaultData = array();
		$uploadFile = ff('file');
		foreach($uploadFile['tmp_name'] as $key => $value){
			$this->type->defaultData[] = mime_content_type($value);
		}
	}
}
?>
