<?php
class BlogModel extends ContentModel{
	function BlogModel(){
		ContentModel::ContentModel('blog');
		$this->icon = $this->imageLoader(tt('icon'), 'files/blog/');
		$this->intro = $this->text(tt('introduction'));
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'intro');
	}
}
?>
