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
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_pttest');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_pttest_data_manager', 'index');
		$this->addAccessMethod('rtna_pttest_data_manager', 'write');
		$this->addAccessMethod('rtna_pttest_data_manager', 'insert');
		$this->addAccessMethod('rtna_pttest_data_manager', 'edit');
		$this->addAccessMethod('rtna_pttest_data_manager', 'update');
		$this->addAccessMethod('rtna_pttest_data_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>