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

		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_classLog');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_classlog_manager', 'index');
		$this->addAccessMethod('rtna_classlog_manager', 'write');
		$this->addAccessMethod('rtna_classlog_manager', 'insert');
		$this->addAccessMethod('rtna_classlog_manager', 'edit');
		$this->addAccessMethod('rtna_classlog_manager', 'update');
		$this->addAccessMethod('rtna_classlog_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
