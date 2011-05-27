<?php
class ImageLoaderColumn extends ModelColumn{
	private $path;
	
	function ImageLoaderColumn($label, $path){
		$this->setType('char');
		$this->label = $label;
		$this->path = $path;
		$this->help = tt('Click on image to upload or change image.');
	}
	
	public function renderForm($formID){
		head_add_js('include/javascript/imageloader.js');
		head_add_js_var('uploadSuccess', tt('image successfully uploaded'));
		$id = $formID.'_'.$this->name;
		if(strlen($this->data)) $imageSource = ROOT_URI.$this->data;
		else $imageSource = ROOT_URI.'files/icon/loader.png';
		$this->setFormAttribute('type', 'hidden');
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('value', $this->data);
		$this->setFormAttribute('id', 'input_'.$id);
		$render = '
		<input '.$this->renderFormAttribute().'/>
		<a href="#" onclick="showImageLoader(\''.$id.'\', \''.$this->path.'\');return false;">
			<img src="'.$imageSource.'" border="0" id="image_'.$id.'" alt="image"/>
		</a>
		<div id="loader_'.$id.'" style="display:none;"></div>';
		return $render;
	}
}

?>
