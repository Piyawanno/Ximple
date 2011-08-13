<?php
class TabMenuModel extends Model{
	public $moduleName = 'requirement';
	public $tableName = 'requirement_menu';
	public $dropMode = 'requirement_drop_menu';
	
	function TabMenuModel($requirementID=null){
		$this->menu_name = $this->char(tt('name'));
		$this->menu_description = $this->plain(tt('description'));
		$this->requirement = $this->none($requirementID, 'int');
		$this->requirement->isGridForm = false;
		$this->requirement->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->requirement->data = $parentID;
	}
}
?>
