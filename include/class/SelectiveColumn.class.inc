<?php
class SelectiveColumn extends ModelColumn{
	function SelectiveColumn($label, $option, $help=null){
		$this->type = 'char';
		$this->label = $label;
		$this->help = $help;
		$this->option = $option;
	}
	
	function triggerSelect(){
		if(!is_array($this->data)){
			$this->data = $this->option[$this->data];
		}
	}
}
?>
