<?php
include_once('peopleinfo.tool.inc');

class PeopleRelationModel extends Model{
	function PeopleRelationModel($informationID=null){
		$this->people = $this->select(tt('related person'), peopleinfo_get_people_name());
		$this->relation = $this->select(tt('relation'), peopleinfo_get_relation());
		$this->information = $this->none($informationID, 'int');
		$this->information->isGridForm = false;
	}
	
	public function triggerSetParent($parentID){
		$this->information->defaultData = $parentID;
	}
}
?>
