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
		$this->formMeta->mode = 'forum_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
	
	public function save(){
		config_set('forum_entry_appearance', pp('forum_appearance'));
		$levelNumber = pp('forum_user_level_number');
		$levelName = pp('forum_user_level_name');
		$level = array();
		foreach($levelNumber as $key => $value){
			if(strlen($levelName[$key]) and ((int) $value) > 0){
				$level[$value] = $levelName[$key];
			}
		}
		ksort($level);
		config_set('forum_user_level', $level);
		ContentConfig::save();
	}
	
	protected function groupConfigForm(){
		ContentConfig::groupConfigForm();
		$userLevel = $this->getNewConfigForm(tt('User Levels'));
		$userLevel->append('forum_user_level');
	}
}
?>
