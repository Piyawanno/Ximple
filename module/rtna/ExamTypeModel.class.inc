<?php
	class ExamTypeModel extends Model{
	function ExamTypeModel(){
		$this->exam_type = $this->title(tt('exam type'));
		$this->section = $this->section();
	}
}
?>