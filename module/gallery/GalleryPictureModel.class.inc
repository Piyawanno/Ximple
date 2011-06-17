<?php
require_once(INCLUDE_PATH.'tool/image.tool.inc');
require_once('GalleryPictureColumn.class.inc');

class GalleryPictureModel extends Model{
	function GalleryPictureModel($galleryID){
		$this->gallery = $this->hidden($galleryID, 'int');
		$this->picture = new GalleryPictureColumn($galleryID);
		$this->post_time = $this->now();
	}
}
?>
