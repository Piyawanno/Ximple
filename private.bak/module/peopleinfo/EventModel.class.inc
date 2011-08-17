<?php
include_once(MODULE_PATH.'freetag/FreeTagColumn.class.inc');

class EventModel extends Model{
	function EventModel(){
		$this->event = $this->title(tt('event'));
		$this->event->listMode = 'peopleinfo_event';
		
		$this->place = $this->autoComplete(tt('place'), 'peopleinfo_event_get_defined_place');
		$this->place->isList = true;
		$this->place->listMode = 'peopleinfo_event_place';
		$this->place->isReachable = true;
		$this->place->isNotNull = true;
		
		$this->occur_date = $this->calendar('date');
		$this->occur_date->isList = true;
		
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		$this->update_time->formatDateBySelect = true;
		$this->update_time->dateFormat = cc('time_format').' H:i';
		
		$this->creator = $this->owner();
		
		$this->description = $this->text(tt('description'));
		$this->description->isReachable = true;
		
		$this->freetag = new FreeTagColumn('peopleinfo_event');
		$this->section = $this->section();
	}
}
?>
