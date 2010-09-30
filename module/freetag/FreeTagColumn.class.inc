<?php
class FreeTagColumn extends ModelColumn{
	function FreeTagColumn(){
		$this->type = 'shorttext';
		$this->form = 'autocomplete';
		$this->label = tt('tags');
		$this->help = tt('Use comma for multiple tags.');
		$this->ajaxMode = 'freetag_get_ajax';
	}
	
	public function triggerSelect(){
		$this->data = input_split_comma($this->data);
	}
	
	public function triggerPostInsert(){
		$this->vadiladeTag();
	}
	
	public function triggerPostUpdate(){
		$this->vadiladeTag();
	}
	
	private function vadiladeTag(){
		$tagArray = input_split_comma($this->data);
		if(count($tagArray)) $this->data = join(', ', $tagArray).', ';
		else $this->data = '';
	}
}
?>
