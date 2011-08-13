<?php
execute_add_extended_class('evaluation', 'config', 'EvaluationConfig');
include_once(INCLUDE_PATH.'class/ConfigControl.class.inc');
include('EvaluationConfigModel.class.inc');

class EvaluationConfig extends ConfigControl{
	function EvaluationConfig(){
		$this->moduleName = 'evaluation';
		$this->moduleExtension = 'config';
		$this->moduleTitle = tt('Evaluation Configuration');
		$this->setAdmin('evaluation_admin');
		$this->init(new EvaluationConfigModel());
	}
	
	public function index(){
		document_set_path(tt('Evaluation'), 'evaluation');
		$this->formMeta->mode = 'evaluation_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
