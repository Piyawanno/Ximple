<?php
class JournalModel extends ContentModel{
	function JournalModel(){
		ContentModel::ContentModel('journal');
		$this->checkPath();
		$this->icon = $this->imageLoader(tt('icon'), 'files/journal/');
		$this->intro = $this->text(tt('introduction'));
		$this->intro->enableTranslate();
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'intro');
	}
	
	private function checkPath(){
		$path  = ROOT_PATH.'files/journal/';
		if(!is_dir($path))  mkdir($path);
	}
}
?>
