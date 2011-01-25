<?php
include_once('Authority.class.inc');

abstract class Translatable extends Authority{
	private $translateFormRender;
	
	protected $moduleName;
	protected $moduleTitle;
	protected $modelConnector;
	protected $configForm = array();
	protected $formMeta;
	
	public function renderTranslateForm(){
		execute_set_ajax();
		$supportedLanguage = cc('supported_language');
		$this->formMeta->id = $this->moduleName;
		$this->formMeta->title = sprintf(tt('Translation : %s'), $supportedLanguage[gg('language')]);
		$this->formMeta->mode = $this->moduleName.'_translate';
		$this->prepareTranslateForm();
		$translation = translate_get_all_data($this->moduleName, gg('module_id'), gg('language'));
		$render = $this->translateFormRender->renderTranslateForm($translation);
		return $render;
	}
	
	public function setTranslate(){
		execute_set_ajax();
		translate_set_data(pp());
		return tt('Your form has been successfully translated.');
	}
	
	protected function translateData(){
		foreach($this->data as $key => $value){
			$this->data[$key] = translate_content($value, $this->moduleName, $value['id']);
		}
	}
	
	protected function translateDataByID(){
		$this->dataByID = translate_content($this->dataByID, $this->moduleName, $this->id);
	}
	
	private function prepareTranslateForm(){
		if(!$this->translateFormRender){
			include_once('FormRender.class.inc');
			include_once('TranslateFormRender.class.inc');
			$this->translateFormRender = new TranslateFormRender($this->modelConnector, $this->formMeta);
		}
		$this->formMeta->configForm = $this->configForm;
		if($this->formMeta->isSetTitle){
			document_set_title($this->formMeta->title);
		}
	}
}
?>
