<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');
include('PeopleRelationModel.class.inc');
include('EventRelationModel.class.inc');
include('PeopleFileModel.class.inc');

class InformationModel extends Model{
	function InformationModel(){
		$this->topic = $this->title(tt('topic'));
		$this->topic->isList = true;
		$this->topic->isReachable = true;
		
		$this->source_date = $this->calendar(tt('date'));
		
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		
		$this->freetag = new FreeTagColumn('peopleinfo_info');
		
		$this->people = $this->grid('');
		$this->people->setModel('peopleinfo', 'people_relation', new PeopleRelationModel());
		$this->people->isDB = false;
		
		$this->event = $this->grid(tt('related event'));
		$this->event->setModel('peopleinfo', 'event_relation', new EventRelationModel());
		$this->event->isDB = false;
		
		$this->file = $this->grid(tt('related files'));
		$this->file->setModel('peopleinfo', 'people_file', new PeopleFileModel());
		$this->file->isDB = false;
		$this->file->isDropByUpdate = false;
		
		$this->section = $this->section();
	}
}
?>
