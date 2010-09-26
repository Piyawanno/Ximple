<?php
class FreeTagColumn extends ModelColumn{
	function FreeTagColumn(){
		$this->type = 'shorttext';
		$this->form = 'autocomplete';
		$this->label = tt('tags');
		$this->help = tt('Use comma for multiple tags.');
		$this->ajaxMode = 'freetag_get_ajax';
	}
	
	function triggerSelect(){
		$this->data = input_split_comma($this->data);
	}
	
	function triggerPostInsert(){
		$this->data = join(', ', input_split_comma($this->data)).', ';
	}
	
	function triggerPostUpdate(){
		$this->data = join(', ', input_split_comma($this->data)).', ';
	}
}
?>
