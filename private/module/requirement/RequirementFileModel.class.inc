<?php
class RequirementFileModel extends Model{
	public $moduleName = 'requirement';
	public $tableName = 'requirement_file';
	public $dropMode = 'requirement_drop_file';
	
	function RequirementFileModel($requirementID=null){
		$this->short_description = $this->char(tt('short description'));
		$this->file = $this->file(tt('file'), 'files/requirement/'.SECTION.'/');
		$this->requirement = $this->none($requirementID, 'int');
		$this->requirement->isGridForm = false;
		$this->requirement->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->requirement->data = $parentID;
	}
}
?>
