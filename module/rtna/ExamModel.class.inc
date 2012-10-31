<?php
require_once('rtna.tool.inc');
require_once('CadetClassLogModel.class.inc');
class ExamModel extends Model{
	function ExamModel(){
		$this->lecture_class = $this->select(tt('class'), rtna_get_lectureClass_option());
		$this->exam_time = $this->timestamp(tt('examination time'));
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>