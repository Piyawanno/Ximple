<?php
execute_add_extended_class('rtna', 'bedroom', 'Bedroom');
include('BedroomModel.class.inc');

class Bedroom extends Control{
	function Bedroom(){
		$this->moduleTitle = tt('Bedroom');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'bedroom';
		$this->tableName = 'rtna_bedroom';
		$this->init(new BedroomModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_bedroom');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_bedroom_data_manager', 'index');
		$this->addAccessMethod('rtna_bedroom_data_manager', 'write');
		$this->addAccessMethod('rtna_bedroom_data_manager', 'insert');
		$this->addAccessMethod('rtna_bedroom_data_manager', 'edit');
		$this->addAccessMethod('rtna_bedroom_data_manager', 'update');
		$this->addAccessMethod('rtna_bedroom_data_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
