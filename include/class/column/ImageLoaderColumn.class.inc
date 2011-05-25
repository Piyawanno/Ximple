<?php
class ImageLoaderColumn extends ModelColumn{
	private $path;
	
	function ImageLoaderColumn($label, $path){
		$this->setType('char');
		$this->label = $label;
		$this->path = $path;
		$this->help = tt('Click on image to upload or change image.');
	}
	
	public function renderFoorm(){
		$id = $form_id.'_'.$name;
		if(strlen($this->data)) $imageSource = ROOT_URI.$this->data;
		else $imageSource = ROOT_URI.'files/icon/loader.png';
		$this->setFormAtrribute('type', 'hidden');
		$this->setFormAtrribute('name', $this->name);
		$this->setFormAtrribute('value', $this->data);
		$this->setFormAtrribute('id', 'input_'.$id);
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
