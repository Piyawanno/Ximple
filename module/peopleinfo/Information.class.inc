<?php
if(execute_get_class('peopleinfo') == null){
	execute_add_class('peopleinfo', 'Information');
}

include_once('InformationModel.class.inc');
include_once('peopleinfo.tool.inc');

class Information extends Control{
	function Information(){
		$this->moduleTitle = tt('Information');
		$this->moduleName = 'people';
		$this->tableName = 'information';
		$this->setAdmin('peopleinfo_admin');
		$this->init(new InformationModel());
	}
}

?>
