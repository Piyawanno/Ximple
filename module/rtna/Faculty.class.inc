<?php
execute_add_extended_class('rtna', 'faculty', 'Faculty');
include('FacultyModel.class.inc');

class Faculty extends Control{
	function Faculty(){
		$this->moduleTitle = tt('Faculty');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'faculty';
		$this->tableName = 'rtna_faculty';
		$this->init(new FacultyModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_faculty');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_faculty_manager', 'index');
		$this->addAccessMethod('rtna_faculty_manager', 'write');
		$this->addAccessMethod('rtna_faculty_manager', 'insert');
		$this->addAccessMethod('rtna_faculty_manager', 'edit');
		$this->addAccessMethod('rtna_faculty_manager', 'update');
		$this->addAccessMethod('rtna_faculty_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>