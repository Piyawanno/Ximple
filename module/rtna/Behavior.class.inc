<?php
execute_add_extended_class('rtna', 'behavior', 'Behavior');
include('BehaviorModel.class.inc');

class Behavior extends Control{
	function Behavior(){
		$this->moduleTitle = tt('Behavior');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'behavior';
		$this->tableName = 'rtna_behavior';
		$this->init(new BehaviorModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_behavior');
	}
}
?>