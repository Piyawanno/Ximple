<?php
execute_add_extended_class('rtna', 'pttest', 'PTTest');
include('PTTestModel.class.inc');

class PTTest extends Control{
	function PTTest(){
		$this->moduleTitle = tt('PTTest');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'pttest';
		$this->tableName = 'rtna_pttest';
		$this->init(new PTTestModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_pttest');
	}
}
?>