<?php
execute_add_extended_class('rtna', 'activity', 'Activity');
include('ActivityModel.class.inc');

class Activity extends Control{
	function Activity(){
		$this->moduleTitle = tt('Activity');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'activity';
		$this->tableName = 'rtna_activity';
		$this->init(new ActivityModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_activity');
	}
}
?>