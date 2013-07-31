<?php
class CadetActivityModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_cadet_activity';
	public $dropMode = 'rtna_cadet_activity_drop';
	
	function CadetActivityModel($activityID=null){
		$this->activity = $this->none($activityID, 'int');
		$this->activity->isGridForm = false;
		$this->activity->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
	}
	
	public function triggerSetParent($parentID){
		$this->activity->data = $parentID;
	}
}
?>