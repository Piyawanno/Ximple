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
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_lectureClass');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_lecture_class_manager', 'index');
		$this->addAccessMethod('rtna_lecture_class_manager', 'write');
		$this->addAccessMethod('rtna_lecture_class_manager', 'insert');
		$this->addAccessMethod('rtna_lecture_class_manager', 'edit');
		$this->addAccessMethod('rtna_lecture_class_manager', 'update');
		$this->addAccessMethod('rtna_lecture_class_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
