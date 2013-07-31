<?php
require_once('rtna.tool.inc');
require_once('CadetActivityModel.class.inc');

class ActivityModel extends Model{
	function ActivityModel(){
		$this->name = $this->title(tt('Activity name'));
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->create_date = $this->now();
		$this->start_time = $this->calendar(tt('start time'));
        $this->end_time = $this->calendar(tt('end time'));
		$this->cadet = $this->grid(tt('cadet'))->setModel(new CadetActivityModel());
		$this->section = $this->section();
	}
}
?>