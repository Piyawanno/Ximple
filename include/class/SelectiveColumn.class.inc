<?php
class SelectiveColumn extends ModelColumn{
	function SelectiveColumn($label, $slection, $help=null){
		$this->type = 'char';
		$this->label = $label;
		$this->help = $help;
	}
	
	function triggerSelect(){
		if(!is_array($this->data)) $this->data = $this->selection[$this->data];
	}
}
?>
