<?php
execute_add_class('journal', 'JournalConfig');
include_once(ROOT_PATH.'module/content/ContentConfig.class.inc');
include('JournalConfigModel.class.inc');

class JournalConfig extends ContentConfig{
	function JournalConfig(){
		$this->moduleName = 'journal_config';
		$this->moduleTitle = tt('Journal Configuration');
		$this->setAdmin('journal_admin');
		$this->addAction('journal_config', 'index');
		$this->addAction('journal_config_save', 'save');
		$this->init(new JournalConfigModel());
		$this->setMode('journal');
	}
	
	public function index(){
		document_set_path(tt('Journal'), 'journal');
		$this->groupConfigForm();
		$this->appearanceFormGroup->append('journal_entries_number');
		$this->formMeta->mode = 'journal_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
