<?php
require_once(ROOT_PATH.'include/class/MultipleFilesColumn.class.inc');
require_once(ROOT_PATH.'include/tool/image.tool.inc');
require_once('GalleryPictureColumn.class.inc');

class GalleryPictureModel extends Model{
	function GalleryPictureModel($galleryID){
		$this->gallery = $this->hidden($galleryID, 'int');
		$this->picture = new GalleryPictureColumn($galleryID);
		$this->post_time = $this->now();
	}
}
?>
