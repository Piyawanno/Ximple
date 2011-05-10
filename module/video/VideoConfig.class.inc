<?php
execute_add_extended_class('video', 'config', 'VideoConfig');
include_once(ROOT_PATH.'module/content/ContentConfig.class.inc');
include('VideoConfigModel.class.inc');

class VideoConfig extends ContentConfig{
	function VideoConfig(){
		$this->moduleName = 'video';
		$this->moduleTitle = tt('Video Configuration');
		$this->setAdmin('video_admin');
		$this->addAction('video_config', 'index');
		$this->addAction('video_config_save', 'save');
		$this->init(new VideoConfigModel());
		$this->setMode('video');
	}
	
	public function index(){
		document_set_path(tt('Video'), 'video');
		$this->groupConfigForm();
		$this->appearanceFormGroup->append('video_width');
		$this->appearanceFormGroup->append('video_height');
		$this->appearanceFormGroup->append('video_entries_number');
		$this->formMeta->mode = 'video_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
