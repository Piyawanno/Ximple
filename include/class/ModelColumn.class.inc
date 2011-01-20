<?php
class ModelColumn{
	private $allowedType = array(
		'int',
		'real',
		'char',
		'shorttext',
		'text',
		'date',
		'timestamp',
		'array'
	);
	
	private $selectiveForm = array(
		'radio',
		'checkbox',
		'select',
		'multiseclect',
		'checkedit'
	);
	
	private $allowedForm = array(
		'none',
		'char',
		'password',
		'file',
		'multiplefiles',
		'hidden',
		'text',
		'plain',
		'shorttext',
		'calendar',
		'captcha',
		'autocomplete',
		'group',
		'email',
		'imageloader',
		'color',
		'grid',
		'uri',
	);
	
	private $allowedTranslateForm = array(
		'char',
		'plain',
		'text',
		'shorttext'
	);
	
	private $typeMap = array(
		'int' => 'integer',
		'real' => 'float',
		'char' => 'string',
		'shorttext' => 'string',
		'text' => 'string',
		'date' => 'string',
		'timestamp' => 'string',
		'array' => 'array',
	);
	
	public $type;
	public $label;
	public $help;
	public $form;
	public $dateFormat = 'd F Y';
	public $option;
	public $data;
	public $defaultData;
	public $path;
	public $ajaxMode;
	public $listMode;
	public $maxWidth;
	
	public $isDB = true;
	public $isForm = true;
	public $isNotNull = false;
	public $isSerialize = false;
	public $isList = false;
	public $isReachable = false;
	public $isOrderable = true;
	public $isSortable = false;
	public $isAllTags = false;
	public $isImage = false;
	public $isExceptedAdmin = true;
	public $isExceptedGuest = false;
	public $isUpdateTime = false;
	public $isMultipleInsert = false;
	public $isTranslation = false;
	
	public function getPHPType(){
		return $this->typeMap[$this->type];
	}
	
	public function enableTranslation(){
		if(in_array($this->form, $this->allowedTranslateForm)){
			$this->isTranslation = true;
		}elseif(state_is_develop()){
			$pattern = tt('%s is not allowed to be translated.');
			notify_add_error(sprintf($pattern, $this->form));
		}
	}
	
	public function setDefault($data){
		$this->defaultData = $data;
		settype($this->defaultData, $this->typeMap[$this->type]);
	}
	
	public function check(){
		$message = $this->checkType();
		if($message !== null) return $message;
		$message = $this->checkForm();
		if($message !== null) return $message;
		$message = $this->checkPath();
		if($message !== null) return $message;
		$message = $this->checkDefault();
		return $message;
	}
	
	private function checkType(){
		if(!in_array($this->type, $this->allowedType)) {
			return 'unkown type : '.$this->type;
		}
		return null;
	}
	
	private function checkForm(){
		if(in_array($this->form, $this->selectiveForm)){
			if(!is_array($this->option)){
				return 'unset option';
			}
		}elseif(!in_array($this->form, $this->allowedForm)){
			return 'unkown form : '.$this->form;
		}
		return null;
	}
	
	private function checkPath(){
		if($this->form == 'file' and !strlen($this->path)){
			return 'unset file path';
		}
		return null;
	}
	
	private function checkDefault(){
		if($this->defaultData and !$this->form){
			$this->form = 'hidden';
			return 'defaultData exists form is not set (form is automatically set to hidded)';
		}
		return null;
	}
}
?>
