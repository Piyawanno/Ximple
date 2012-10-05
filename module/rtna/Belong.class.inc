<?php
execute_add_extended_class('rtna', 'belong', 'Belong');
include('BelongModel.class.inc');

class Belong extends Control{
	function Belong(){
		$this->moduleTitle = tt('Belong');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'belong';
		$this->tableName = 'rtna_belong';
		$this->init(new BelongModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_belong_list');
	}

	public function index(){
		
	}
	
	public function dropResolver(){
		db_dropjk('develcard_resolver', (int)gg('id'));
	}

	public function renderClassList(){
		document_set_path(tt('belong class'), 'rtna_belong_class');
		
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_belong_data_manager', 'index');
		$this->addAccessMethod('rtna_belong_data_manager', 'write');
		$this->addAccessMethod('rtna_belong_manager', 'insert');
		
	}

	private function setAction(){
		$this->addAction('rtna_belong_class', 'renderClassList');
		$this->addAction('develcard_drop_resolver', 'dropResolver');
	}
}
?>