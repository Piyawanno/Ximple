<?php
class ModelColumn{
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
	public $selection;
	public $data;
	public $defaultData;
	public $path;
	public $ajaxMode;
	public $listMode;
	public $maxWidth;
	
	public $isDB = true;
	public $isNotNull = false;
	public $isSerialize = false;
	public $isList = false;
	public $isReachable = false;
	public $isOrderable = true;
	public $isSortable = false;
	public $isConfigForm = false;
	public $isAllTags = false;
	public $isImage = false;
	public $isExceptedAdmin = true;
	public $isExceptedGuest = false;
	public $isUpdateTime = false;
	
	public function getPHPType(){
		return $this->typeMap[$this->type];
	}
	
	public function setDefault($data){
		$this->defaultData = $data;
		settype($this->defaultData, $this->typeMap[$this->type]);
	}
	
	public function check(){
		$allowedType = array('int', 'real', 'char', 'shorttext', 'text', 'date', 'timestamp', 'array');
		if(!in_array($this->type, $allowedType)) return 'unkown type : '.$this->type;
		
		$selectionForm = array('radio', 'checkbox', 'select', 'multiseclect', 'checkedit');
		$allowedForm = array(
			'none', 'char', 'password', 'file', 'multifile',
			'hidden', 'text', 'plain', 'shorttext', 'calendar',
			'captcha', 'autocomplete', 'group', 'email', 'imageloader',
			'color', 'grid', 'uri',
		);
		
		if(in_array($this->form, $selectionForm)){
			if(!is_array($this->selection)){
				return 'unset selection';
			}
		}elseif(!in_array($this->form, $allowedForm)){
			return 'unkown form : '.$this->form;
		}
		
		if($this->form == 'file' and !strlen($this->path)){
			return 'unset file path';
		}
		
		if($this->defaultData and !$this->form){
			$this->form = 'hidden';
			return 'defaultData exists form is not set (form is automatically set to hidded)';
		}
		
		return null;
	}
}
?>
