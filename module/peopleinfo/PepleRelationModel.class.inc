<?php
class PeopleRelationModel extends Model{
	function PeopleRelationModel($informationID){
		$this->people = $this->select(tt('related person'), people_get_people());
		$this->information = $this->hidden($informationID);
		$this->relation = $this->select(tt('relation'), people_get_people_relation());
	}
}
?>
