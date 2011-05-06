<?php
include_once('peopleinfo.tool.inc');
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');

class PeopleModel extends Model{
	function PeopleModel($userID){
		$this->user_id = $this->hidden($userID, 'int');
		$this->profile = $this->text('generic information');
		$this->status = $this->radio(tt('status'), peopleinfo_get_people_status());
		$this->freetag = new FreeTagColumn();
		$this->freetag->isReachable = true;
	}
}
?>
