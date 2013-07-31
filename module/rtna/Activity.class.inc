<?php
execute_add_extended_class('rtna', 'activity', 'Activity');
include('ActivityModel.class.inc');

class Activity extends Control{
	function Activity(){
		$this->moduleTitle = tt('Activity');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'activity';
		$this->tableName = 'rtna_activity';
		$this->init(new ActivityModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_activity');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_activity_manager', 'index');
		$this->addAccessMethod('rtna_activity_manager', 'write');
		$this->addAccessMethod('rtna_activity_manager', 'insert');
		$this->addAccessMethod('rtna_activity_manager', 'edit');
		$this->addAccessMethod('rtna_activity_manager', 'update');
		$this->addAccessMethod('rtna_activity_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>