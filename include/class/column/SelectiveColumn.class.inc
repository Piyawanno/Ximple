<?php
abstract class SelectiveColumn extends ModelColumn{
	public $option;
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
}
?>
