<?php
execute_add_extended_class('meeting', 'config', 'MeetingConfig');
include_once(MODULE_PATH.'content/ContentConfig.class.inc');
include_once('MeetingConfigModel.class.inc');

class MeetingConfig extends ContentConfig{
	function MeetingConfig(){
		$this->moduleName = 'meeting';
		$this->moduleExtension = 'config';
		$this->moduleTitle = tt('Meeting Configuration');
		$this->setAdmin('meeting_admin');
		$this->init(new MeetingConfigModel());
		$this->setMode('meeting');
	}
	
	public function index(){
		document_set_path(tt('Meeting'), 'meeting');
		$this->groupConfigForm();
		$this->formMeta->mode = 'meeting_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
