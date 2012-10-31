<?php
execute_add_extended_class('rtna', 'behavior', 'Behavior');
include('BehaviorModel.class.inc');

class Behavior extends Control{
	function Behavior(){
		$this->moduleTitle = tt('Behavior');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'behavior';
		$this->tableName = 'rtna_behavior';
		$this->init(new BehaviorModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_behavior');
	}
	
	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_behavior_manager', 'index');
		$this->addAccessMethod('rtna_behavior_manager', 'write');
		$this->addAccessMethod('rtna_behavior_manager', 'insert');
		$this->addAccessMethod('rtna_behavior_manager', 'edit');
		$this->addAccessMethod('rtna_behavior_manager', 'update');
		$this->addAccessMethod('rtna_behavior_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
