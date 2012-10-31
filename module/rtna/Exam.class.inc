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
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_exam');
	}
}
?>
