<?php
require_once('HiddenColumn.class.inc');
class FileSizeColumn extends HiddenColumn{
	function FileSizeColumn($label, $help=null){
		$this->setType('int');
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
