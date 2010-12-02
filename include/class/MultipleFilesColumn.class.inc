<?php
class MultipleFilesColumn extends ModelColumn{
	private $columnName;
	private $fileArray;
	
	function MultipleFilesColumn($label, $path, $columnName, $help=null){
		$this->type = 'char';
		$this->form = 'multiplefiles';
		$this->columnName = $columnName;
		$this->label = $label;
		$this->path = $path;
		$this->help = $help;
		$this->data = array();
		$this->multipleInsert = true;
	}
	
	public function triggerPostInsert(){
		$this->upload();
	}
	
	public function triggerPostUpdate(){
		$this->upload();
	}
	
	private function upload(){
		$this->fileArray = input_reorder_multiple_files();
		foreach($this->fileArray as $key => $value){
			$this->data[] = io_upload($value, $this->path, $this->isImage);
		}
	}
}
?>
