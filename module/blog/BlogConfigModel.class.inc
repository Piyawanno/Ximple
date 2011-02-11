<?php
class BlogConfigModel extends ContentConfigModel{
	function BlogConfigModel(){
		ContentConfigModel::ContentConfigModel('blog');
		
		$option = array(
			'avatar' => tt('show avatar'),
			'category_icon' => tt('show category icon'),
			'comment_avatar' => tt('show avatar for comments'),
			'signature' => tt('user signature'),
			'sibling' => tt('next/previous entry'),
		);
		$this->blog_appearance = $this->checkbox(tt('show in rendered blog'), $option);
		
		$option = array(3 => 3, 5 => 5, 8 => 8, 10 => 10, 15 => 15, 20 => 20);
		$this->blog_entries_number = $this->select(tt('blog entries per page'), $option);
		$this->extendBefore('blog_comment_write_label', 'blog_entries_number');
	}
}
?>
