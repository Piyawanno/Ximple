<?php
require_once('rtna.tool.inc');
require_once('CadetExamModel.class.inc');
class ExamModel extends Model{
	function ExamModel(){
		$this->lecture_class = $this->select(tt('class'), rtna_get_lectureClass_option());
		$this->exam_type = $this->select(tt('type'), rtna_get_examType_option());
		
		$uri = SECTION_URI.Q.'rtna_examType_write';
		$pattern = tt('You can add new type with <a href="%s">this page</a>.');
		$help = sprintf($pattern, $uri);
		$this->exam_type = $this->select(tt('type'), rtna_get_examType_option(), $help);
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->fullpoint = $this->spin(tt('full point'), 0);
		$this->cadet = $this->grid(tt('cadet'))->setModel(new CadetExamModel());
		$this->section = $this->section();
	}
}
?>