<?php
require_once('CharColumn.class.inc');
class FileColumn extends CharColumn{
	public $isImage = false;
	protected $fileArray;
	
	function FileColumn($label, $path, $help=null){
		CharColumn::CharColumn($label, $help);
		$this->path = $path;
		$this->isOrderable = false;
		$this->setFormAttribute('size', 25);
		$this->setFormAttribute('type', 'file');
	}
	
	public function triggerPostInsert(){
		if($this->isMultipleInsert) $this->multipleInsert(); 
		else $this->singleInsert();
	}
	
	public function triggerPostUpdate(){
		if($this->isMultipleInsert) $this->multipleUpdate();
		else $this->singleUpdate();
	}
	
	private function singleInsert(){
		$file = ff($this->name);
		if($file['size']){
			$this->data = io_upload($file, $this->path, $this->isImage);
		}
	}
	
	private function multipleInsert(){
		$this->fileArray = input_reorder_multiple_files($this->name);
		foreach($this->fileArray as $key => $value){
			if($value['size']){
				$this->data[] = io_upload($value, $this->path, $this->isImage);
			}else{
				unset($this->fileArray[$key]);
				$this->data[] = null;
			}
		}
	}
	
	private function singleUpdate(){
		$file = ff($this->name);
		if($file['size']){
			if(is_file(ROOT_PATH.$this->data)) unlink(ROOT_PATH.$this->data);
			$this->data = io_upload($file, $this->path, $this->isImage);
		}
	}
}
?>
