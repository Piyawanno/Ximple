<?php
abstract class ModelColumn{
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
	
	private $type;
	
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
	
	public abstract function enableTranslate();
	
	public function check(){
	
	}
	
	public function getPHPType(){
		return $this->typeMap[$this->type];
	}
	
	public function setType($type){
		if(!in_array($this->type, $this->allowedType) and state_is_develop()) {
			notify_add_error('unkown type : '.$this->type.' ('.$this->name.')');
		}
	}
	
	public function getType(){
		return $type;
	}
	
	protected function enableTranslateError(){
		if(state_is_develop()){
			$pattern = tt('%s is not allowed to be translated.');
			notify_add_error(sprintf($pattern, $this->name));
		}
	}
}
?>
