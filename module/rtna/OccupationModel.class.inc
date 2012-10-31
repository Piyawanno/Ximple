<?php
require_once('rtna.tool.inc');

class OccupationModel extends Model{
	function OccupationModel(){
		$this->classroom = $this->select(tt('classroom'), rtna_get_classroom_option());
		$this->lecture_class = $this->select(tt('lecture class'), rtna_get_lectureclass_option());
		$this->class_time = $this->timestamp(tt('class time'));
		$this->section = $this->section();
		
	}

}
?>