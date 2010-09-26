<?php

include_once(ROOT_PATH.'include/tool/form.tool.inc');

class FormRender{
	private $modelConnector;
	private $formMeta;
	private $notNull;
	private $label;
	private $help;
	private $renderedConfigForm = '';
	
	function FormRender($modelConnector, $formMeta){
		$this->modelConnector = $modelConnector;
		$this->formMeta = $formMeta;
	}
	
	public function renderInsertForm(){
		$this->modelConnector->triggerInsertForm();
		$model = $this->modelConnector->resetData();
		$this->prepareRender();
		return $this->renderForm($model);
	}
	
	public function renderUpdateForm($data){
		$model = $this->modelConnector->setData($data);
		$this->modelConnector->triggerUpdateForm();
		$this->prepareRender();
		return $this->renderForm($model);
	}
	
	private function renderForm($model){
		$model = $this->modelConnector->getFormColumn();
		$form = form($this->formMeta->id, $model);
		$extensionArg = array($form, $this->formMeta);
		$form = extension_execute('pre_render_form', $extensionArg, $form);
		$rednerArray = array(
			'form' => $form,
			'meta' => $this->formMeta,
			'help' => $this->help,
			'label' => $this->label,
			'not_null' => $this->notNull,
			'config' => $this->renderedConfigForm,
		);
		$render = render($rednerArray, 'form.tpl', 'render_form');
		$render = extension_execute('post_render_form', $render, $render);
		return $render;
	}
	
	private function prepareRender(){
		if($this->formMeta->isCaptcha){
			$this->modelConnector->initCaptchaColumn();
		}
		$this->notNull = $this->modelConnector->getColumnNameByBoolean('isNotNull');
		$this->label = $this->modelConnector->getColumnAttribute('label');
		$hidden = $this->modelConnector->getColumnNameByAttribute('form', 'hidden');
		foreach($hidden as $name){
			if(isset($this->label[$name])) unset($this->label[$name]);
		}
		$this->help = $this->modelConnector->getColumnAttribute('help');
		head_add_js_array('notNull'.$this->formMeta->id, $this->notNull);
		head_add_js_array('label'.$this->formMeta->id, $this->label);
		$this->renderConfigForm();
	}
	
	private function renderConfigForm(){
		foreach($this->formMeta->configForm as $configForm){
			$this->renderedConfigForm .= $configForm->render($this->formMeta);
		}
	}
}

?>
