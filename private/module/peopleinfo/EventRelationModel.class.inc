<?php
class EventRelationModel extends Model{
	public $moduleName = 'peopleinfo';
	public $tableName = 'event_relation';
	public $dropMode = 'peopleinfo_info_drop_event_relation';
	
	function EventRelationModel($informationID=null){
		$this->tableName = 'event_relation';
		$this->event = $this->select(tt('event'), peopleinfo_get_event());
		$this->information = $this->none($informationID, 'int');
		$this->information->isGridForm = false;
		$this->information->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->information->data = $parentID;
	}
}
?>
