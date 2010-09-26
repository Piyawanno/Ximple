<?php
class FileSizeColumn extends ModelColumn{
	function FileSizeColumn($label, $help=null){
		$this->form = 'hidden';
		$this->type = 'int';
		$this->defaultData = 0;
		$this->label = $label;
		$this->help = $help;
		$this->isList = true;
	}
	
	public function triggerSelect(){
		$this->data = render_file_size($this->data);
	}
}
?>
