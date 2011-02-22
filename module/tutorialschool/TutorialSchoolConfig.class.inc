<?php
execute_add_class('tutorialschool', 'TutorialSchoolConfig');
include_once(ROOT_PATH.'module/content/ContentConfig.class.inc');
include('TutorialSchoolConfigModel.class.inc');

class TutorialSchoolConfig extends ContentConfig{
	function TutorialSchoolConfig(){
		$this->moduleName = 'tutorialschool_config';
		$this->moduleTitle = tt('TutorialSchool Configuration');
		$this->setAdmin('tutorialschool_admin');
		$this->addAction('tutorialschool_config', 'index');
		$this->addAction('tutorialschool_config_save', 'save');
		$this->init(new TutorialSchoolConfigModel());
		$this->setMode('tutorialschool');
	}
	
	public function index(){
		document_set_path(tt('TutorialSchool'), 'tutorialschool');
		$this->groupConfigForm();
		$this->appearanceFormGroup->append('tutorialschool_entries_number');
		$this->formMeta->mode = 'tutorialschool_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
