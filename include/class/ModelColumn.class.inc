<?php
abstract class ModelColumn{
	private $type;
	private $formAttribute = array();
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
	
	protected $isAllowedTranslate = false;
	protected $isTranslate = false;
	
	public $name;
	public $label;
	public $help;
	public $data;
	public $defaultData;
	
	public $ajaxMode;
	public $listMode;
	
	public $isDB = true;
	public $isNotNull = false;
	public $isList = false;
	public $isReachable = false;
	public $isOrderable = true;
	public $isSortable = false;
	public $isAllHTMLTags = false;
	public $isParent = false;
	
	public abstract renderForm($formID);
	
	public function enableTranslate(){
		if($this->isAllowedTranslate){
			$this->isTranslate = true;
		}elseif(state_is_develop()){
			$pattern = tt('%s is not allowed to be translated.');
			notify_add_error(sprintf($pattern, $this->name));
		}
	}
	
	public function check(){
	}
	
	public function setFormAttribute($name, $value){
		$this->formAttribute[$name] = $value;
	}
	
	public function getPHPType(){
		return $this->typeMap[$this->type];
	}
	
	public function setType($type){
		$allowedType = array_keys($this->typeMap);
		if(!in_array($this->type, $allowedType) and state_is_develop()) {
			notify_add_error('unkown type : '.$type.' ('.$this->name.')');
		}
	}
	
	public function getType(){
		return $type;
	}
	
	protected function renderFormAttribute(){
		$render = '';
		foreach($this->formAttribute as $key => $value){
			$render .= $key.'="'.$value.'" ';
		}
		return $render;
	}
}
?>
