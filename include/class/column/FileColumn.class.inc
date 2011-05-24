<?php
require_once('CharColumn.class.inc');
class FileColumn extends ModelColumn{
	public $isImage = false;
	
	function FileColumn($label, $path, $help=null){
		$this->setType('char');
		$this->label = $label;
		$this->help = $help;
		$this->path = $path;
		$this->setFormAtrribute('size', 25);
		$this->setFormAtrribute('type', 'hidden');
	}
	
	public function triggerPostInsert(){
		$file = ff($this->name);
		if($file['size']){
			$this->data = io_upload($file, $this->path, $this->isImage);
		}
	}
	
	public function triggerPostUpdate(){
		$file = ff($this->name);
		if($file['size']){
			if(is_file(ROOT_PATH.$this->data)) unlink(ROOT_PATH.$this->data);
			$this->data = io_upload($file, $this->path, $this->isImage);
		}
	}
}
?>
