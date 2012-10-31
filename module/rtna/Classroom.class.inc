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

		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_classroom');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_classroom_manager', 'index');
		$this->addAccessMethod('rtna_classroom_manager', 'write');
		$this->addAccessMethod('rtna_classroom_manager', 'insert');
		$this->addAccessMethod('rtna_classroom_manager', 'edit');
		$this->addAccessMethod('rtna_classroom_manager', 'update');
		$this->addAccessMethod('rtna_classroom_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
