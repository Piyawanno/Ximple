<?php
execute_add_extended_class('peopleinfo', 'info', 'Information');

include_once('InformationModel.class.inc');
include_once('peopleinfo.tool.inc');

class Information extends Control{
	function Information(){
		$this->moduleTitle = tt('Information');
		$this->moduleName = 'peopleinfo';
		$this->tableName = 'information';
		$this->setAdmin('peopleinfo_admin');
		$this->init(new InformationModel());
	}
}

?>
