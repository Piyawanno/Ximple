<?php
require_once('rtna.tool.inc');
require_once('ClubMemberModel.class.inc');
class EducationyearModel extends Model{
	function EducationyearModel(){
		$this->start_time = $this->calendar(tt('start time'));
        $this->end_time = $this->calendar(tt('end time'));
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>