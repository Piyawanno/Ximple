<?php
class RequirementLinkModel extends Model{
	public $moduleName = 'requirement';
	public $tableName = 'requirement_link';
	public $dropMode = 'requirement_drop_link';
	
	function RequirementLinkModel($requirementID=null){
		$this->url = $this->char(tt('URL'));
		$this->link_description = $this->plain(tt('description'));
		$this->requirement = $this->none($requirementID, 'int');
		$this->requirement->isGridForm = false;
		$this->requirement->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->requirement->data = $parentID;
	}
}
?>
