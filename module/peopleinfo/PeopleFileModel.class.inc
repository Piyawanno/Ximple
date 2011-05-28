<?php
class PeopleFileModel extends Model{
	public $moduleName = 'peopleinfo';
	public $tableName = 'people_file';
	public $dropMode = 'peopleinfo_info_drop_people_file';
	
	function PeopleFileModel($informationID=null){
		$this->tableName = 'people_file';
		$this->short_description = $this->title(tt('short description'));
		$this->file = $this->file('file', 'files/peopleinfo/');
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
		foreach($this->file->data as $key => $value){
			if(is_file($value)){
				$this->type->data[$key] = mime_content_type($value);
			}
		}
	}
}
?>
