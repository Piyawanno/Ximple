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
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_club');
	}
}
?>
