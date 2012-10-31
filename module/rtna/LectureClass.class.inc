<?php
execute_add_extended_class('rtna', 'lectureClass', 'LectureClass');
include('LectureClassModel.class.inc');

class LectureClass extends Control{
	function LectureClass(){
		$this->moduleTitle = tt('LectureClass');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'lectureClass';
		$this->tableName = 'rtna_lectureClass';
		$this->init(new LectureClassModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_lectureClass');
	}
}
?>
