<?php
execute_add_extended_class('locale', 'module', 'LocaleModule');

require_once(INCLUDE_PATH.'class/ConfigControl.class.inc');
require_once('LocaleModuleModel.class.inc');
require_once('locale.tool.inc');

if(!state_is_develop()) error_denied();

class LocaleModule extends ConfigControl{
	function LocaleModule(){
		$this->moduleName = 'locale';
		$this->moduleExtension = 'module';
		$this->moduleTitle = tt('Initial Locale of Module');
		$this->setAdmin('locale_admin');
		$this->init(new LocaleModuleModel());
	}
	
	public function index(){
		document_set_path(tt('Locale'), 'locale');
		document_set_path($this->moduleTitle);
		$this->formMeta->mode = 'locale_module_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
	
	public function save(){
		execute_set_db();
		document_set_redirect('locale_module');
		locale_init_module(pp('module'));
	}
}
?>
