<?php
require_once('FileColumn.class.inc');

class ImageColumn extends FileColumn{
	private $maxWidth;
	
	function ImageColumn($label, $path, $maxWidth=600, $help=null){
		FileColumn::FileColumn($label, $path, $help);
		$this->maxWidth = $maxWidth;
		$modelColumn->help = $help.tt('Image must be only .png or .jpeg or .jpg. ');
		$modelColumn->help.= sprintf(tt('For image wider than %dpx, it will be automatically resized.'), $maxWidth);
	}
	
	public function triggerPostInsert(){
		require_once(ROOT_PATH.'include/tool/image.tool.inc');
		FileColumn::triggerPostInsert();
		$this->checkImage();
	}
	
	public function triggerPostUpdate(){
		require_once(ROOT_PATH.'include/tool/image.tool.inc');
		FileColumn::triggerPostUpdate();
		$this->checkImage();
	}
	
	private function checkImage(){
		$file = ff($this->name);
		if($file['size']){
			image_check_max_width($file, ROOT_PATH.$this->path, $this->maxWidth);
		}	
	}
}
?>
