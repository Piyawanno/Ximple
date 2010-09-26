<?php
execute_add_class('contact', 'ContactConfig');
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include('ContactConfigModel.class.inc');

class ContactConfig extends ConfigControl{
	function ContactConfig(){
		$this->moduleName = 'contact_config';
		$this->moduleTitle = tt('Contact Configuration');
		$this->setAdmin('contact_admin');
		$this->addAction('contact_config', 'index');
		$this->addAction('contact_config_save', 'save');
		$this->init(new ContactConfigModel());
	}
	
	public function index(){
		document_set_path(tt('Contact'), 'contact');
		$this->formMeta->mode = 'contact_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
