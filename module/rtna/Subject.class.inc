<?php
execute_add_extended_class('rtna', 'subject', 'Subject');
include('SubjectModel.class.inc');

class Subject extends Control{
	function Subject(){
		$this->moduleTitle = tt('Subject');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'subject';
		$this->tableName = 'rtna_subject';
		$this->init(new SubjectModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_subject');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_subject_manager', 'index');
		$this->addAccessMethod('rtna_subject_manager', 'write');
		$this->addAccessMethod('rtna_subject_manager', 'insert');
		$this->addAccessMethod('rtna_subject_manager', 'edit');
		$this->addAccessMethod('rtna_subject_manager', 'update');
		$this->addAccessMethod('rtna_subject_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
