<?php
abstract class SelectiveColumn extends ModelColumn{
	public $option;
	protected $formClass;
	
	function SelectiveColumn($label, $option, $help=null){
		$this->setType('char');
		$this->label = $label;
		$this->help = $help;
		$this->option = $option;
	}
	
	public function check(){
		if(!is_array($this->option) and state_is_develop()){
			notify_add_error('Option of '.$this->name.' is not set.');
		}
	}
	
	public function triggerSelect(){
		if(!is_array($this->data)){
			$this->data = $this->option[$this->data];
		}
	}
	
	protected function renderRawsForm($formID){
		$id = $formID.'_'.$name;
		$render = '<ul class="'.$this->formClass.'" id="'.$id.'">';
		$this->setFormAtrribute('name', $this->name);
		$this->setFormAtrribute('style', 'border:none;');
		foreach($modelCol->option as $key => $value){
			$this->setFormAtrribute('value', $value);
			$this->getCheck($key);
			$render .= '<li><input '.$this->renderFormAttribute().'/>%s</li>'
		}
		$render .= '</ul>';
		$render .= '<span id="info_'.$id.'"></span>';
		$render .= '<p style="clear:both;">';
		return $render;
	}
	
	protected function getCheck($data){
	}
}
?>
