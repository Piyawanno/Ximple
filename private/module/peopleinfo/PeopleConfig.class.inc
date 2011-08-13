<?php
execute_add_extended_class('peopleinfo', 'config', 'PeopleConfig');

include_once(INCLUDE_PATH.'class/ConfigControl.class.inc');
include_once('PeopleConfigModel.class.inc');

class PeopleConfig extends ConfigControl{
	function PeopleConfig(){
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'config';
		$this->moduleTitle = tt('People Information Center Configuration');
		$this->setAdmin('peopleinfo_admin');
		$this->init(new PeopleConfigModel());
	}
	
	public function index(){
		document_set_path(tt('People'), 'peopleinfo');
		$this->formMeta->mode = 'peopleinfo_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
	
	public function save(){
		$type = pp('peopleinfo_data_type');
		foreach($type as $key => $value){
			if(strlen($value) == 0) unset($type[$key]);
		}
		config_set('peopleinfo_data_type', $type);
		ConfigControl::save();
	}
}
?>
