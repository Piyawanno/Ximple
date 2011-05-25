<?php
class ImageColumn extends FileColumn{
	private $maxWidth;
	
	function ImageColumn($label, $path, $maxWidth=600, $help=null){
		FileColumn::FileColumn($label, $path, $help);
		$this->maxWidth = $maxWidth;
		$modelColumn->help = $help.tt('Image must be only .png or .jpeg or .jpg. ');
		$modelColumn->help.= sprintf(tt('For image wider than %dpx, it will be automatically resized.'), $maxWidth);
	}
	
	public function triggerPostInsert(){
		FileColumn::triggerPostInsert();
		image_check_max_width(ff($this->name), ROOT_PATH.$this->path, $this->maxWidth);
	}
	
	public function triggerPostUpdate(){
		FileColumn::triggerPostUpdate();
		image_check_max_width(ff($this->name), ROOT_PATH.$this->path, $this->maxWidth);
	}
}
?>
