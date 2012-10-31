<?php
execute_add_extended_class('rtna', 'health', 'Health');
include('HealthModel.class.inc');

class Health extends Control{
	function Health(){
		$this->moduleTitle = tt('Health');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'health';
		$this->tableName = 'rtna_health';
		$this->init(new HealthModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_health');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_health_data_manager', 'index');
		$this->addAccessMethod('rtna_health_data_manager', 'write');
		$this->addAccessMethod('rtna_health_data_manager', 'insert');
		$this->addAccessMethod('rtna_health_data_manager', 'edit');
		$this->addAccessMethod('rtna_health_data_manager', 'update');
		$this->addAccessMethod('rtna_health_data_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>