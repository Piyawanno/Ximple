<?php
execute_add_class('forum', 'ForumConfig');
include_once(ROOT_PATH.'module/content/ContentConfig.class.inc');
include('ForumConfigModel.class.inc');

class ForumConfig extends ContentConfig{
	function ForumConfig(){
		$this->moduleName = 'forum_config';
		$this->moduleTitle = tt('Forum Configuration');
		$this->setAdmin('forum_admin');
		$this->addAction('forum_config', 'index');
		$this->addAction('forum_config_save', 'save');
		$this->init(new ForumConfigModel());
		$this->setMode('forum');
	}
	
	public function index(){
		document_set_path(tt('Forum'), 'forum');
		$this->groupConfigForm();
		$this->appearanceFormGroup->append('forum_entries_number');
		$this->formMeta->mode = 'forum_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
