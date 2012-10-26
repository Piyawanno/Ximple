<?php
execute_add_extended_class('rtna', 'health', 'Health');
include('HealthModel.class.inc');

class Health extends Control{
	function Health(){
		$this->moduleTitle = tt('Health');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'health';
		$this->tableName = 'rtna_health';
		$this->init(new HealthModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_health');
		}
}
?>