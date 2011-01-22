<?php
class TranslateFormRender extends FormRender{
	private $moduleID;
	
	function TranslateFormRender($modelConnector, $formMeta){
		FormRender::FormRender($modelConnector, $formMeta);	
	}
	
	public function renderTranslateForm($data=array()){
		$this->prepareRender();
		$this->label['status'] = tt('status');
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'submitTranslateForm';
		return FormRender::renderForm();
	}
	
	protected function checkTranslate(){
		$this->isTranslate = false;
	}
	
	protected function getFormColumn(){
		$model = $this->modelConnector->getTranslateFormColumn();
		$additionalModel = $this->getAdditionalModel();
		return array_merge($additionalModel, $model);
	}
	
	private function getAdditionalModel(){
		$statusOption = array(
			0 => tt('draft'),
			1 => tt('published'),
		);
		return array(
			'status' => Model::select(tt('status'), $statusOption),
			'language' => Model::hidden(gg('language')),
			'module' => Model::hidden(gg('module')),
			'module_id' => Model::hidden(gg('module_id')),
		);
	}
}
?>
