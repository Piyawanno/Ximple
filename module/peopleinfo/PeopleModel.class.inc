<?php
require_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');
require_once('peopleinfo.tool.inc');
require('PeopleColumn.class.inc');

class PeopleModel extends Model{
	function PeopleModel(){
		$this->people = new PeopleColumn();
		$this->status = $this->select(tt('status'), peopleinfo_get_people_status());
		$this->status->isList = true;
		
		$this->profile = $this->text('generic information');
		$this->profile->isReachable = true;
		
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		
		$this->freetag = new FreeTagColumn('peopleinfo');
		$this->section = $this->section();
	}
	
	public function triggerSelect(){
		$this->people->option = peopleinfo_get_people_name();
	}
}
?>
