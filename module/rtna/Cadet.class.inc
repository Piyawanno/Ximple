<?php
execute_add_class('rtna', 'Cadet');
include('CadetModel.class.inc');

class Cadet extends Control{
	function Cadet(){
		$this->moduleTitle = tt('RTNA Database');
		$this->moduleName = 'rtna';
		$this->tableName = 'cadet';
		
		$this->setAdmin('rtna_admin');
		$this->init(new CadetModel());
		
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
}
?>
