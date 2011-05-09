<?php
execute_add_class('peopleinfo', 'People');

include_once('PeopleModel.class.inc');
include_once('peopleinfo.tool.inc');

class People extends Control{
	function People(){
		$this->moduleTitle = tt('People');
		$this->moduleName = 'peopleinfo';
		$this->tableName = 'people';
		$this->setAdmin('peopleinfo_admin');
		$this->init(new PeopleModel());
	}
}

?>
