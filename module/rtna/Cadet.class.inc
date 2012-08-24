<?php
execute_add_extended_class('rtna', 'cadet', 'Cadet');
include('CadetModel.class.inc');

class Cadet extends Control{
	function Cadet(){
		$this->moduleTitle = tt('Cadet'); //tt
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'cadet';
		$this->tableName = 'rtna_cadet';
		$this->init(new CadetModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_cadet_list');
	}

	public function index(){
		
	}

	public function renderClassList(){
		document_set_path(tt('Cadet class'), 'rtna_cadet_class');
		
	}

	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_cadet_data_manager', 'index');
		$this->addAccessMethod('rtna_cadet_data_manager', 'write');
		$this->addAccessMethod('rtna_cadet_data_manager', 'insert');
		
	}

	private function setAction(){
		$this->addAction('rtna_cadet_class', 'renderClassList');
	}
}
?>
