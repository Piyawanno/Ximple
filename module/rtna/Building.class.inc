<?php
execute_add_extended_class('rtna', 'building', 'Building');
include('BuildingModel.class.inc');

class Building extends Control{
	function Building(){
		$this->moduleTitle = tt('Building');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'building';
		$this->tableName = 'rtna_building';
		$this->init(new BuildingModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_building');
	}
	
	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_building_manager', 'index');
		$this->addAccessMethod('rtna_building_manager', 'write');
		$this->addAccessMethod('rtna_building_manager', 'insert');
		$this->addAccessMethod('rtna_building_manager', 'edit');
		$this->addAccessMethod('rtna_building_manager', 'update');
		$this->addAccessMethod('rtna_building_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
