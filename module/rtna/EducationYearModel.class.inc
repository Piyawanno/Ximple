<?php
require_once('rtna.tool.inc');
class EducationYearModel extends Model{
	function EducationYearModel(){
		$this->education_year = $this->spin(tt('education year'), 2012);
		$this->start_time = $this->calendar(tt('start time'));
        $this->end_time = $this->calendar(tt('end time'));
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>