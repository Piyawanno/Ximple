<?php
class FileColumn extends ModelColumn{
	public $isImage = false;
	
	function FileColumn($label, $path, $help=null){
		$this->setType('char');
		$this->label = $label;
		$this->help = $help;
		$this->path = $path;
	}
	
	public function enableTranslate(){
		$this->enableTranslateError();
	}
	
	public function renderForm($formID){
		$render = '<input name="'.$this->name.'" id="'.$formID.'" value="'.$this->data.'" type="file"/>';
		$render.= '<span id="info_'.$formID.'_'.$this->name.'"></span>';
		return $render;
	}
	
	public function renderGridForm($formID){
		return '<input name="'.$this->name.'[]" value="'.$this->data.'" type="file"/>';
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
