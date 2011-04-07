<?php
require_once(ROOT_PATH.'include/class/MultipleFilesColumn.class.inc');
require_once(ROOT_PATH.'include/tool/image.tool.inc');

class GalleryPictureModel extends Model{
	function GalleryPictureModel($galleryID){
		$this->gallery = $this->hidden($galleryID, 'int');
		$this->picture = new GalleryPictureColumn($galleryID);
		$this->post_time = $this->now();
	}
}

class GalleryPictureColumn extends MultipleFilesColumn{
	function GalleryPictureColumn($galleryID){
		$this->galleryID = $galleryID;
		$label = tt('');
		$this->path = ROOT_PATH.'files/gallery/'.$galleryID.'/';
		MultipleFilesColumn::MultipleFilesColumn($label, $this->path, 'picture');
	}
	
	function triggerPostInsert(){
		MultipleFilesColumn::triggerPostInsert();
		$thumbpath = $this->path.'thumb_';
		foreach($this->fileArray as $key => $value){
			image_generate_thumb($value, $this->path.'/'.$value['name'], $thumbpath.$value['name']);
		}
		
		foreach($this->data as $key => $value){
			$this->data[$key] = str_replace('files/gallery/'.$this->galleryID.'/', '', $value);
		}
	}
	
	function triggerDrop(){
	}
}
?>
