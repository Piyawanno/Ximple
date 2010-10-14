<?php
execute_add_class('blog', 'BlogConfig');
include_once(ROOT_PATH.'module/content/ContentConfig.class.inc');
include('BlogConfigModel.class.inc');

class BlogConfig extends ContentConfig{
	function BlogConfig(){
		$this->moduleName = 'blog_config';
		$this->moduleTitle = tt('Blog Configuration');
		$this->setAdmin('blog_admin');
		$this->addAction('blog_config', 'index');
		$this->addAction('blog_config_save', 'save');
		$this->init(new BlogConfigModel());
		$this->setMode('blog');
	}
	
	public function index(){
		document_set_path(tt('Blog'), 'blog');
		$this->groupConfigForm();
		$this->appearanceFormGroup->append('blog_entries_number');
		$this->formMeta->mode = 'blog_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
