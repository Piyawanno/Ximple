<?php
class HitDictPictureModel extends Model{
	public $moduleName = 'hitdict';
	public $tableName = 'hitdict_picture';
	public $dropMode = 'hitdict_picture_drop';
	
	function HitDictPictureModel($hid=null){
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
		$path = 'files/hitdict/';
		if(!is_dir(ROOT_PATH.$path)) mkdir(ROOT_PATH.$path);
		return $path;
	}
}
?>
