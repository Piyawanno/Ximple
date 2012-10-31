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
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_building');
	}
}
?>
