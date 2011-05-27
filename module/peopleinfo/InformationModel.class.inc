<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');
include('PeopleRelationModel.class.inc');
include('EventRelationModel.class.inc');
include('PeopleFileModel.class.inc');

class InformationModel extends Model{
	function InformationModel(){
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = 'peopleinfo_info';
		
		$this->source_date = $this->calendar(tt('date'));
		
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		$this->freetag = new FreeTagColumn('peopleinfo_info');
		
		$this->people = $this->grid('')->setModel(new PeopleRelationModel());
		$this->event = $this->grid('')->setModel(new EventRelationModel());
		$this->file = $this->grid('')->setModel(new PeopleFileModel());
		$this->file->isEmptyForm = true;
		
		$this->section = $this->section();
	}
}
?>
