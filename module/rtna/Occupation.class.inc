<?php
execute_add_extended_class('rtna', 'occupation', 'Occupation');
include('OccupationModel.class.inc');

class Occupation extends Control{
	function Occupation(){
		$this->moduleTitle = tt('Occupation');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'occupation';
		$this->tableName = 'rtna_occupation';
		$this->init(new OccupationModel());
		
		$this->setAccess();
		$this->setAction();

		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_occupation');
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_occupation_manager', 'index');
		$this->addAccessMethod('rtna_occupation_manager', 'write');
		$this->addAccessMethod('rtna_occupation_manager', 'insert');
		$this->addAccessMethod('rtna_occupation_manager', 'edit');
		$this->addAccessMethod('rtna_occupation_manager', 'update');
		$this->addAccessMethod('rtna_occupation_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
