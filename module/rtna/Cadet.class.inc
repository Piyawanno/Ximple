<?php
execute_add_class('rtna', 'Cadet');
include('CadetModel.class.inc');

class Cadet extends Control{
	function Cadet(){
		$this->moduleTitle = tt('Cadet');
		$this->moduleName = 'rtna';
		$this->tableName = 'cadet';
		$this->init(new CadetModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_list');
	}

	public function index(){
		
	}

	public function renderClassList(){
		
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_cadet_data_manager', 'index');
		$this->addAccessMethod('rtna_cadet_data_manager', 'write');
	}

	private function setAction(){
		$this->addAction('rtna_class', 'renderClassList');
	}
}
?>
