<?php
require_once('GalleryPictureModel.class.inc');

class GalleryPicture extends Control{
	private $galleryID;
	
	function GalleryPicture($galleryID=null){
		$this->galleryID = $galleryID;
		$this->tableName = 'gallery_picture';
		$this->moduleName = 'gallery';
		$this->moduleTitle = tt('Gallery Picture');
		$this->init(new GalleryPictureModel($galleryID));
		$this->formMeta->id = 'gallery_picture';
		$this->formMeta->title = tt('Insert Picture');
		$this->formMeta->mode = 'gallery_picture_insert';
		$this->formMeta->isSetTitle = false;
	}
	
	public function drop(){
		$this->id = (int) gg('id');
		$this->selectByID($this->column, true);
		$path = ROOT_PATH.'files/gallery/'.$this->galleryID.'/';
		unlink($path.$this->dataByID['picture']);
		unlink($path.'thumb_'.$this->dataByID['picture']);
		Control::drop();
	}
	
	public function getPictures(){
		$this->select($this->column, 'WHERE gallery='.((int) $this->galelryID));
	}
	
	public function allowAccess(){
		$this->setOwner(USER_ID);
	}
}
?>
