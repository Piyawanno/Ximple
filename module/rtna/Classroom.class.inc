<?php
execute_add_extended_class('rtna', 'classroom', 'Classroom');
include('ClassroomModel.class.inc');

class Classroom extends Control{
	function Classroom(){
		$this->moduleTitle = tt('Classroom');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'classroom';
		$this->tableName = 'rtna_classroom';
		$this->init(new ClassroomModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_classroom');
	}
}
?>
