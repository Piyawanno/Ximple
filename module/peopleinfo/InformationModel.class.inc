<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');
include('PeopleRelationModel.class.inc');
include('EventRelationModel.class.inc');
include('PeopleFileModel.class.inc');

class InformationModel extends Model{
	function InformationModel($id){
		$this->topic = $this->title(tt('topic'));
		$this->topic->isList = true;
		$this->topic->isReachable = true;
		
		$this->source_date = $this->calendar(tt('date'));
		
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		
		$this->freetag = new FreeTagColumn();
		
		$this->people = $this->grid(tt('related people'));
		$this->people->setModel('peopleinfo', new PeopleRelationModel($id));
		$this->people->isDB = false;
		
		$this->event = $this->grid(tt('related event'));
		$this->event->setModel('peopleinfo', new EventRelationModel($id));
		$this->event->isDB = false;
		
		$this->file = $this->grid(tt('related files'));
		$this->file->setModel('peopleinfo', new PeopleFileModel($id));
		$this->file->isDB = false;
		
		$this->section = $this->section();
	}
}
?>
