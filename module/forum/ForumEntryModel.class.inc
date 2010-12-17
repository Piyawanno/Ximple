<?php
class ForumEntryModel extends ContentModel{
	function ForumEntryModel(){
		ContentModel::ContentModel('forumentry');
		$this->checkPath();
		$this->icon = $this->imageLoader(tt('icon'), 'files/forum/');
		$this->intro = $this->text(tt('introduction'));
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'intro');
	}
	
	private function checkPath(){
		$path  = ROOT_PATH.'files/forum/';
		if(!is_dir($path))  mkdir($path);
	}
}
?>
