<?php
class MultipleFilesColumn extends ModelColumn{
	private $columnName;
	protected $fileArray;
	
	function MultipleFilesColumn($label, $path, $columnName, $help=null){
		$this->type = 'char';
		$this->form = 'multiplefiles';
		$this->columnName = $columnName;
		$this->label = $label;
		$this->path = $path;
		$this->help = $help;
		$this->isMultipleInsert = true;
	}
	
	public function triggerPostInsert(){
		$this->upload();
	}
	
	public function triggerPostUpdate(){
		$this->upload();
	}
	
	private function upload(){
		$this->fileArray = input_reorder_multiple_files($this->columnName);
		foreach($this->fileArray as $key => $value){
			if($value['size']){
				$fileName = io_upload($value, $this->path, $this->isImage);
				$this->data[] = $fileName;
			}else{
				unset($this->fileArray[$key]);
			}
		}
	}
}
?>
