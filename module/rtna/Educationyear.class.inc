<?php
execute_add_extended_class('rtna', 'educationyear', 'Educationyear');
include('EducationyearModel.class.inc');

class Educationyear extends Control{
	function Educationyear(){
		$this->moduleTitle = tt('Educationyear');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'educationyear';
		$this->tableName = 'rtna_educationyear';
		$this->init(new EducationyearModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_educationyear');
	}
}
?>
