<?php
require_once('CheckSlideDualColumn.class.inc');

class ImageLoaderColumn extends ModelColumn{
	public $isResize = true;
	
	private $path;
	private $width;
	private $height;
	private $slideDrop;
	private $separateSection = true;
	
	function ImageLoaderColumn($label, $path, $width=64, $height=null){
		$this->setType('char');
		$this->label = $label;
		$this->path = $path;
		$this->width = $width;
		$this->height = ($height == null) ? $width : $height;
		$option = array(
			0 => tt('enabled'),
			1 => tt('disabled'),
		);
		$this->slideDrop = new CheckSlideDualColumn('', $option);
		$this->help = tt('Click on image to upload or change image.');
		$this->checkPath();
	}
	
	public function triggerGetJavaScript(){
		head_add_js('include/javascript/imageloader.js');
		head_add_js_var('uploadSuccess', tt('image successfully uploaded'));
		$this->slideDrop->triggerGetJavaScript();
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$this->name;
		$this->slideDrop->name = $this->name.'_check';
		if(strlen($this->data)) $imageSource = ROOT_URI.$this->data;
		else $imageSource = ROOT_URI.'files/icon/loader.png';
		$this->setFormAttribute('type', 'hidden');
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('value', $this->data);
		$this->setFormAttribute('id', 'input_'.$id);
		if(strlen($this->data)) $slide = $this->slideDrop->renderForm($formID);
		else $slide = '';
		$render = '
		<input '.$this->renderFormAttribute().'/>
		<a href="#" onclick="showImageLoader(\''.$id.'\', \''.$this->path.'\', '.((int) $this->width).', '.((int) $this->height).', '.((int) $this->isResize).');return false;">
			<img src="'.$imageSource.'" border="0" id="image_'.$id.'" alt="image" style="max-width:100%;"/>
		</a>
		<p>'.$slide.'</p>
		<div id="loader_'.$id.'" style="display:none;"></div>';
		return $render;
	}
	
	public function triggerPostUpdate(){
		if(pp($this->name.'_check') == '1') $this->data = "";
	}
	
	private function checkPath(){
		if($this->separateSection){
			if(!is_dir(ROOT_PATH.$this->path)) mkdir(ROOT_PATH.$this->path);
			$this->path = $this->path.SECTION.'/';
			if(!is_dir(ROOT_PATH.$this->path)) mkdir(ROOT_PATH.$this->path);
		}
	}
}
?>
