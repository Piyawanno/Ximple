<?php
require_once('rtna.tool.inc');

class SubjectModel extends Model{
	function SubjectModel(){
		$this->subject = $this->title(tt('subject'));
		$this->faculty = $this->select(tt('faculty'), rtna_get_faculty_option());
		$this->classroom = $this->select(tt('classroom'), rtna_get_classroom_option());
		$this->education_year = $this->select(tt('education year'), rtna_get_educationYear_option());
		$this->class_time = $this->timestamp(tt('class time'));
		$this->section = $this->section();
		
	}

}
?>