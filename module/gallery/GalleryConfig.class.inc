<?php
execute_add_class('gallery', 'GalleryConfig');
include_once(ROOT_PATH.'module/content/ContentConfig.class.inc');
include('GalleryConfigModel.class.inc');

class GalleryConfig extends ContentConfig{
	function GalleryConfig(){
		$this->moduleName = 'gallery_config';
		$this->moduleTitle = tt('Gallery Configuration');
		$this->setAdmin('gallery_admin');
		$this->addAction('gallery_config', 'index');
		$this->addAction('gallery_config_save', 'save');
		$this->init(new GalleryConfigModel());
		$this->setMode('gallery');
	}
	
	public function index(){
		document_set_path(tt('Gallery'), 'gallery');
		$this->groupConfigForm();
		$this->appearanceFormGroup->append('gallery_entries_number');
		$this->formMeta->mode = 'gallery_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>