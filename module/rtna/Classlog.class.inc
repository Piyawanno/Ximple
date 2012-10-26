<?php
execute_add_extended_class('rtna', 'classLog', 'ClassLog');
include('ClassLogModel.class.inc');

class ClassLog extends Control{
	function ClassLog(){
		$this->moduleTitle = tt('ClassLog');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'classLog';
		$this->tableName = 'rtna_classLog';
		$this->init(new ClassLogModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_classLog');
	}
}
?>
