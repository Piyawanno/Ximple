<?php
class EventRelationModel extends Model{
	function EventRelationModel($informationID=null){
		$this->event = $this->select(tt('event'), peopleinfo_get_event());
		$this->information = $this->hidden($informationID, 'int');
		$this->information->isGridForm = false;
	}
	
	public function triggerSetParent($parentID){
		$this->information->defaultData = $parentID;
	}
}
?>
