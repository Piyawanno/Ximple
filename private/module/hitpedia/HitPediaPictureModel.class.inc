<?php

class HitPediaPictureModel extends Model{
	public $moduleName = 'hitpedia';
	public $tableName = 'hitpedia_picture';
	public $dropMode = 'hitpedia_picture_drop';
	
	function HitPediaPictureModel($hid=null){
		$this->picture = $this->file(tt('picture'), $this->getPath());
		$this->picture->isImage = true;
		$this->description = $this->plain(tt('description'));
		
		$this->hid = $this->none($hid, 'int');
		$this->hid->isGridForm = false;
		$this->hid->isParent = true;
	}
	
	public function triggerSetParent($hid){
		$this->hid->data = $hid;
	}
	
	private function getPath(){
		$path = 'files/hitpedia/';
		if(!is_dir(ROOT_PATH.$path)) mkdir(ROOT_PATH.$path);
		return $path;
	}
}
?>
