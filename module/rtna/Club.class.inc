<?php
execute_add_extended_class('rtna', 'club', 'Club');
include('ClubModel.class.inc');

class Club extends Control{
	function Club(){
		$this->moduleTitle = tt('Club');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'club';
		$this->tableName = 'rtna_club';
		$this->init(new ClubModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_club');
	}
	
	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_club_manager', 'index');
		$this->addAccessMethod('rtna_club_manager', 'write');
		$this->addAccessMethod('rtna_club_manager', 'insert');
		$this->addAccessMethod('rtna_club_manager', 'edit');
		$this->addAccessMethod('rtna_club_manager', 'update');
		$this->addAccessMethod('rtna_club_manager', 'drop');
	}
	
	private function setAction(){
		
	}
}
?>
