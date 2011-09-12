<?php
require_once('FormModelRender.class.inc');
class FormRender extends FormModelRender{
	static public $gridRowArray = array();

	protected $modelConnector;
	protected $isTranslate;
	protected $label;
	protected $formMeta;
	
	private $notNull;
	private $notNullID = array();
	private $help;
	private $formItem;
	private $renderedConfigForm = '';
	private $captchaForm;
	
	private $moduleName;
	private $moduleID;
	
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
		$this->modelConnector->triggerUpdateForm();
		$this->checkTranslate();
		$this->getTranslateLabel();
		$this->modelConnector->setData($data);
		$this->prepareRender();
		return $this->renderForm();
	}
	
	protected function getFormColumn(){
		return $this->modelConnector->getFormColumn();
	}
	
	protected function renderForm(){
		document_init_form();
		$this->prepareHead();
		$renderArray = array(
			'form' => $this->formItem,
			'captcha' => $this->captchaForm,
			'meta' => $this->formMeta,
			'help' => $this->help,
			'label' => $this->label,
			'not_null' => $this->notNull,
			'is_translate' => $this->isTranslate,
			'config' => $this->renderedConfigForm,
		);
		if(!$this->formMeta->isAjax){
			head_add_js_var('modeID', MODE_ID);
			head_add_js_var('moduleName', MODULE);
		}
		$renderArray['rendered_form'] = render($renderArray, 'form.tpl', 'form');
		head_add_js_array('gridRowArray', FormRender::$gridRowArray);
		return render($renderArray, 'form_frame.tpl', 'form_frame');
	}
	
	protected function checkTranslate(){
		$this->isTranslate = $this->modelConnector->hasTranslate();
	}
	
	protected function prepareRender(){
		$this->prepareCaptcha();
		$this->formItem = $this->renderFormModel($this->formMeta->id);
		$this->prepareNotNull();
		$this->prepareLabel();
		$this->help = $this->modelConnector->getColumnAttribute('help');
		$this->renderConfigForm();
		$this->separateCaptcha(); 
	}
	
	private function prepareCaptcha(){
		if($this->formMeta->isCaptcha and authority_is_guest()){
			require_once('column/CaptchaColumn.class.inc');
			$this->modelConnector->addModel('captcha', new CaptchaColumn());
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
			$this->moduleID = $this->modelConnector->getID();
			$this->moduleName = $this->modelConnector->getModuleName();
			head_add_js('include/javascript/translate.js');
			$label = tt('Translate to : ');
			foreach(cc('supported_language') as $key => $value){
				$label .= '<a href="#" onclick="return selectTranslateLanguage(\''.$value.'\', \''.$this->moduleName.'\','.$this->moduleID.')"><img src="'.ROOT_URI.'files/flag/'.$value.'.png"></a> ';
			}
			$this->formMeta->description .= '<p>'.$label.'</p>';
		}
	}
	
	private function separateCaptcha(){
		if(isset($this->formItem['captcha'])){
			$this->captchaForm = array(
				'form' => $this->formItem['captcha'],
				'label' => $this->label['captcha'],
				'help' => $this->help['captcha'],
			);
			unset($this->formItem['captcha']);
		}
	}
}
?>
