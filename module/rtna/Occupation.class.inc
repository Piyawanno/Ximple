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
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_occupation');
	}
}
?>
