<?php
if(execute_get_class('peopleinfo') == null){
	echo('what sap');
	execute_add_class('peopleinfo', 'Event');
}

include_once('EventModel.class.inc');
include_once('peopleinfo.tool.inc');

class Event extends Control{
	function Event(){
		$this->moduleTitle = tt('Event');
		$this->moduleName = 'peopleinfo';
		$this->tableName = 'event';
		$this->setAdmin('peopleinfo_admin');
		$this->init(new EventModel());
	}
}

?>
