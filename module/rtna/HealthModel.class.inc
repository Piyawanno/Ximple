<?php
require_once('rtna.tool.inc');
require_once('CadetHealthModel.class.inc');

class HealthModel extends Model{
	function HealthModel(){
		$this->cadet = $this->grid(tt('cadet'))->setModel(new CadetHealthModel());
		$this->syndrome = $this->shortText(tt('syndrome'));
		$this->syndrome->isList = true;
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->start_time = $this->calendar(tt('start time'));
        $this->end_time = $this->calendar(tt('end time'));
		$this->section = $this->section();
	}
}
?>