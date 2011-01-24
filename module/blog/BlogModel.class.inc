<?php
class BlogModel extends ContentModel{
	function BlogModel(){
		ContentModel::ContentModel('blog');
		$this->checkPath();
		$this->icon = $this->imageLoader(tt('icon'), 'files/blog/');
		$this->intro = $this->text(tt('introduction'));
		$this->intro->enableTranslate();
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'intro');
	}
	
	private function checkPath(){
		$path  = ROOT_PATH.'files/blog/';
		if(!is_dir($path))  mkdir($path);
	}
}
?>
