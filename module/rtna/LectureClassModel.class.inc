<?php
require_once('rtna.tool.inc');
require_once('CadetLectureClassModel.class.inc');
class LectureClassModel extends Model{
	function LectureClassModel(){
		$this->lecture_class = $this->title(tt('class'));
		$this->faculty = $this->select(tt('faculty'), rtna_get_faculty_option());
		$this->education_year = $this->select(tt('education year'), rtna_get_educationYear_option());
		$this->desription = $this->shortText(tt('desription'));
		$this->desription->isList = true;
		$this->cadet = $this->grid(tt('cadet'))->setModel(new CadetLectureClassModel());
		$this->classroom = $this->select(tt('classroom'), rtna_get_classroom_option());
		$this->section = $this->section();
	}
}
?>