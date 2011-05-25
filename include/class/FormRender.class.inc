<?php
class FormRender{
	protected $modelConnector;
	protected $isTranslate;
	protected $label;
	protected $formMeta;
	
	private $notNull;
	private $notNullID = array();
	private $help;
	private $renderedConfigForm = '';
	
	function FormRender($modelConnector, $formMeta){
		$this->modelConnector = $modelConnector;
		$this->formMeta = $formMeta;
	}
	
	public function renderInsertForm(){
		$this->isTranslate = false;
		$this->modelConnector->triggerInsertForm();
		$this->modelConnector->resetData();
		$this->prepareRender();
		return $this->renderForm();
	}
	
	public function renderUpdateForm($data){
		$this->checkTranslate();
		$this->getTranslateLabel();
		$this->modelConnector->setData($data);
		$this->modelConnector->triggerUpdateForm();
		$this->prepareRender();
		return $this->renderForm();
	}
	
	protected function getFormColumn(){
		return $this->modelConnector->getFormColumn();
	}
	
	protected function renderForm(){
		document_init_form();
		$this->prepareHead();
		$rednerArray = array(
			'form' => $this->renderFormModel($this->formMeta->id),
			'meta' => $this->formMeta,
			'help' => $this->help,
			'label' => $this->label,
			'not_null' => $this->notNull,
			'is_translate' => $this->isTranslate,
			'config' => $this->renderedConfigForm,
		);
		$render = render($rednerArray, 'form.tpl', 'render_form');
		return $render;
	}
	
	protected function checkTranslate(){
		$this->isTranslate = $this->modelConnector->hasTranslate();
	}
	
	protected function prepareRender(){
		$this->prepareCaptcha();
		$this->prepareNotNull();
		$this->prepareLabel();
		$this->help = $this->modelConnector->getColumnAttribute('help');
		$this->renderConfigForm();
	}
	
	private function prepareCaptcha(){
		if($this->formMeta->isCaptcha){
			$this->modelConnector->initCaptchaColumn();
		}
	}
	
	private function prepareNotNull(){
		$this->notNull = $this->modelConnector->getColumnNameByBoolean('isNotNull');
		foreach($this->notNull as $key => $value){
			$this->notNullID[$key] = $this->formMeta->id.'_'.$value;
		}
		head_add_js_array('notNull'.$this->formMeta->id, $this->notNullID);
	}
	
	private function prepareLabel(){
		$label = $this->modelConnector->getColumnAttribute('label');
		$isFormLabel = $this->modelConnector->getColumnNameByBoolean('isFormLabel');
		foreach($isFormLabel as $key => $value){
			$this->label[$value] = $label[$value];
		}
		head_add_js_array('label'.$this->formMeta->id, $this->label);
	}
	
	private function renderConfigForm(){
		foreach($this->formMeta->configForm as $configForm){
			$this->renderedConfigForm .= $configForm->render($this->formMeta);
		}
	}
	
	private function getTranslateLabel(){
		if($this->isTranslate){
			$pattern = tt('You can use <a %s><strong>Translate-Form</strong></a> to translate this form.');
			$help = sprintf($pattern, 'href="#" onclick="showTranslateDialog();return false"');
			$this->formMeta->description .= '<p>'.$help.'</p>';
		}
	}
	
	private function prepareHead(){
		head_add_css('form.css');
		head_add_js('include/external/jquery/jquery-form.js');
		head_add_js('include/javascript/formcheck.js');
		head_add_js_var('pleaseFill', tt('Please, fill the required field : '));
		head_add_js_var('formNotCorrect', tt('Any field in the form is not correctly filled. Please correct it and try again.'));
		head_add_js_var('isInstalled', true);
	}
	
	private function renderFormModel($id){
		$modelArray = $this->modelConnector->getFormColumn();
		$render = array();
		foreach($modelArray as $name => $model){
			$render[$name] = $model->renderForm($id);
		}
		return $render;
	}
}

?>
