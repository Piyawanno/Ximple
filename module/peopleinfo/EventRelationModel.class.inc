<?php
class EventRelationModel extends Model{
	function EventRelationModel($informationID=null){
		$this->event = $this->checkbox(tt('event'), peopleinfo_get_event());
		$this->information = $this->hidden($informationID);
	}
}
?>
