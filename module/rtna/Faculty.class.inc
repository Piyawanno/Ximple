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
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_faculty');
	}
}
?>