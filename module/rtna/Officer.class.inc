<?php
execute_add_extended_class('rtna', 'officer', 'Officer');
include('OfficerModel.class.inc');

class Officer extends Control{
	function Officer(){
		$this->moduleTitle = tt('Officer');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'officer';
		$this->tableName = 'rtna_officer';
		$this->init(new OfficerModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_officer_list');
	}

	public function index(){
		
	}

	public function dropResolver(){
		db_dropjk('develcard_resolver', (int)gg('id'));
	}

	public function renderClassList(){
		document_set_path(tt('Officer class'), 'rtna_officer_class');
		
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_officer_data_manager', 'index');
		$this->addAccessMethod('rtna_officer_data_manager', 'write');
		$this->addAccessMethod('rtna_officer_data_manager', 'insert');
		$this->addAccessMethod('rtna_officer_data_manager', 'edit');
		$this->addAccessMethod('rtna_officer_data_manager', 'update');
		$this->addAccessMethod('rtna_officer_data_manager', 'drop');
		
	}

	private function setAction(){
		$this->addAction('rtna_officer_class', 'renderClassList');
		$this->addAction('develcard_drop_resolver', 'dropResolver');
	}
}
?>
