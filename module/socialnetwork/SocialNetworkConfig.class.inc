<?php
execute_add_class('socialnetwork', 'SocialNetworkConfig');
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include('SocialNetworkConfigModel.class.inc');

class SocialNetworkConfig extends ConfigControl{
	function SocialNetworkConfig(){
		$this->moduleName = 'socialnetwork_config';
		$this->moduleTitle = tt('SocialNetwork Configuration');
		$this->setAdmin('socialnetwork_admin');
		$this->addAction('socialnetwork_config', 'index');
		$this->addAction('socialnetwork_config_save', 'save');
		$this->init(new SocialNetworkConfigModel());
	}
	
	public function index(){
		document_set_path(tt('SocialNetwork'), 'socialnetwork');
		$this->formMeta->mode = 'socialnetwork_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
