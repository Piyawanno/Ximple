<?php
execute_add_extended_class('rtna', 'exam', 'Exam');
include('ClassLogModel.class.inc');

class Exam extends Control{
	function Exam(){
		$this->moduleTitle = tt('Exam');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'exam';
		$this->tableName = 'rtna_exam';
		$this->init(new ClassLogModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_exam');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_exam_data_manager', 'index');
		$this->addAccessMethod('rtna_exam_data_manager', 'write');
		$this->addAccessMethod('rtna_exam_data_manager', 'insert');
		$this->addAccessMethod('rtna_exam_data_manager', 'edit');
		$this->addAccessMethod('rtna_exam_data_manager', 'update');
		$this->addAccessMethod('rtna_exam_data_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
