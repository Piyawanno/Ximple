<?php
class BlogConfigModel extends ContentConfigModel{
	function BlogConfigModel(){
		ContentConfigModel::ContentConfigModel('blog');
		$option = array(3 => 3, 5 => 5, 8 => 8, 10 => 10, 15 => 15, 20 => 20);
		$this->blog_entries_number = $this->select(tt('number of shown blog entries per page'), $option);
		$this->extendBefore('blog_comment_write_label', 'blog_entries_number');
	}
}
?>
