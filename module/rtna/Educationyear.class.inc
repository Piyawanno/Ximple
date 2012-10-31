<?php
execute_add_extended_class('rtna', 'educationYear', 'EducationYear');
include('EducationYearModel.class.inc');

class EducationYear extends Control{
	function EducationYear(){
		$this->moduleTitle = tt('EducationYear');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'educationYear';
		$this->tableName = 'rtna_educationYear';
		$this->init(new EducationYearModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_educationYear');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_education_year_manager', 'index');
		$this->addAccessMethod('rtna_education_year_manager', 'write');
		$this->addAccessMethod('rtna_education_year_manager', 'insert');
		$this->addAccessMethod('rtna_education_year_manager', 'edit');
		$this->addAccessMethod('rtna_education_year_manager', 'update');
		$this->addAccessMethod('rtna_education_year_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
