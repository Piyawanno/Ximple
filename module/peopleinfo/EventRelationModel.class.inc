<?php
class EventRelationModel extends Model{
	function EventRelationModel($informationID=null){
		$this->event = $this->select(tt('event'), peopleinfo_get_event());
		$this->information = $this->hidden($informationID, 'int');
		$this->information->isForm = false;
	}
}
?>
