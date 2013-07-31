<?php
class DevelCardFileModel extends Model{
	public $moduleName = 'develcard';
	public $tableName = 'develcard_file';
	public $dropMode = 'develcard_drop_file';
	
	public function DevelCardFileModel($develCardID=null){
		$this->develcard = $this->hidden($develCardID, 'int');
		$this->develcard->isGridForm = false;
		$this->develcard->isParent = true;
		
		$this->short_description = $this->title(tt('short description'));
		$this->file = $this->file(tt('file'), $this->getPath());
	}
	
	public function triggerSetParent($parentID){
		$this->develcard->data = $parentID;
	}
	
	public function triggerPostDBInsert(){
		$this->moveFile();
	}
	
	public function triggerPostDBUpdate(){
		$this->moveFile();
	}
	
	private function moveFile(){
		$clause = "WHERE develcard=".$this->develcard->data;
		$data = db_select_single_column($this->tableName, 'file', $clause);
		$path = $this->getPath();
		foreach($data as $key => $value){
			$parent = substr($value, 0, strrpos($value, '/'));
			if($parent == 'files/develcard/'.$this->develcard->data) break;
			$extension = substr($value, strrpos($value, '.')+1);
			$path = $path.md5(rand()).".".$extension;
			rename($value, $path);
			db_update($this->tableName, array('file' => $path), $key);
		}
	}
	
	private function getPath(){
		$path  = 'files/develcard/';
		if(!is_dir(ROOT_PATH.$path)) mkdir(ROOT_PATH.$path);
		if($this->develcard->data != null){
			$path .= $this->develcard->data."/";
			if(!is_dir(ROOT_PATH.$path)) mkdir(ROOT_PATH.$path);
		}
		return $path;
	}
}
?>
