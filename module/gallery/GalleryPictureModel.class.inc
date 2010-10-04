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
		$label = tt('');
		$path = ROOT_PATH.'files/gallery/'.$galleryID.'/';
		MultipleFilesColumn::MultipleFilesColumn($label, $path);
	}
	
	function triggerInsert(){
		MultipleFilesColumn::triggerInsert();
		foreach($this->data as $key => $value){
			image_generate_thumb($file, $this->path, $thumbpath)
		}
	}
}
?>

