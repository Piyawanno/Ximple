<?php
require_once('CharColumn.class.inc');
class FileColumn extends CharColumn{
	public $isImage = false;
	
	function FileColumn($label, $path, $help=null){
		CharColumn::CharColumn($label, $help);
		$this->path = $path;
		$this->isOrderable = false;
		$this->setFormAttribute('size', 25);
		$this->setFormAttribute('type', 'file');
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
