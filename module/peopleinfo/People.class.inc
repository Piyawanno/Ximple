<?php



class People extends Control{
	function People(){
		$this->moduleTitle = tt('People');
		$this->moduleName = 'people';
		$this->tableName = 'people';
		$this->setAdmin('peopleinfo_admin');
		$this->init(new PeopleModel());
	}
}

?>
