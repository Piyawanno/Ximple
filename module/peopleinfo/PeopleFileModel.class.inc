<?php
class PeopleFileModel extends Model{
	public $moduleName = 'peopleinfo';
	public $tableName = 'people_file';
	public $dropMode = 'peopleinfo_info_drop_people_file';
	
	function PeopleFileModel($informationID=null){
		$this->short_description = $this->title(tt('short description'));
		$this->file = $this->file('file', 'files/peopleinfo/');
		$this->file->isNotNull = true;
		$this->type = $this->hidden('', 'char');
		$this->information = $this->none($informationID, 'int');
		$this->information->isGridForm = false;
		$this->information->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->information->data = $parentID;
	}
	
	public function triggerPostInsert(){
		$this->getType();
	}
	
	public function triggerPostUpdate(){
		$this->getType();
	}
	
	private function getType(){
		$this->type->data = array();
		$uploadFile = ff('file');
		foreach($uploadFile['tmp_name'] as $key => $value){
			if(strlen($value)){
				$this->type->data[] = mime_content_type($value);
			}
		}
	}
}
?>
