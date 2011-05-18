<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');

class EventModel extends Model{
	function EventModel(){
		$this->event = $this->title(tt('event'));
		$this->event->listMode = 'peopleinfo_event';
		
		$this->place = $this->autoComplete(tt('place'), 'peopleinfo_event_get_defined_place');
		$this->place->isList = true;
		$this->place->isReachable = true;
		$this->place->isNotNull = true;
		
		$this->occur_date = $this->calendar('date');
		$this->update_time = $this->now();
		
		$this->description = $this->text(tt('description'));
		$this->description->isReachable = true;
		
		$this->freetag = new FreeTagColumn();
		$this->section = $this->section();
	}
}
?>
