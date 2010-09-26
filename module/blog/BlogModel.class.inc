<?php
class BlogModel extends ContentModel{
	function BlogModel(){
		ContentModel::ContentModel('blog');
		$this->intro = $this->text(tt('introduction'));
		$this->extendAfter('topic', 'intro');
	}
}
?>
