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
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_educationYear');
	}
}
?>
