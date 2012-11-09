<?php
execute_add_extended_class('rtna', 'examType', 'ExamType');
include('ExamTypeModel.class.inc');

class ExamType extends Control{
	function ExamType(){
		$this->moduleTitle = tt('ExamType');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'examType';
		$this->tableName = 'rtna_examType';
		$this->init(new ExamTypeModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_examType');
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
