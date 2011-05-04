<?php
class EventRelationModel extends Model{
	function EventRelationModel($informationID){
		$this->event = $this->checkbox(tt('event'), people_info_get_event());
		$this->information = $this->hidden($informationID);
	}
}
?>
