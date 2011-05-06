<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');

class EventModel extends Model{
	function EventModel(){
		$this->event = $this->title(tt('event'));
		$this->place = $this->title(tt('place'));
		$this->occur_date = $this->calendar('date');
		$this->description = $this->text(tt('description'));
		$this->freetag = new FreeTagColumn();
		$this->section = $this->section();
	}
}
?>
