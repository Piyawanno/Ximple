<?php
class ListPageMetaData{
	public $operation = array();
	public $title;
	public $mode;
	public $page = MODE_PAGE;
	public $description;
	public $writeMode;
	public $writeLabel;
	public $defaultOrder;
	public $defaultOrderDesc;
	
	public function addOperation($mode, $label, $icon){
		$this->operation[$mode]['label'] = $label;
		if(is_file(ROOT_PATH.'files/icon/'.$icon)){
			$this->operation[$mode]['icon'] = 'files/icon/'.$icon;
		}elseif(is_file(ROOT_PATH.'module/'.MODULE.'/theme/'.$icon)){
			$this->operation[$mode]['icon'] = 'module/'.MODULE.'/theme/'.$icon;
		}
	}
}
?>
