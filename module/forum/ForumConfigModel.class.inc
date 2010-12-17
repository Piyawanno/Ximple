<?php
class ForumConfigModel extends ContentConfigModel{
	function ForumConfigModel(){
		ContentConfigModel::ContentConfigModel('forum');
		
		$option = array(
			'avatar' => tt('show avatar'),
			'category_icon' => tt('show category icon'),
			'comment_avatar' => tt('show avatar for comments'),
			'sibling' => tt('next/previous entry'),
		);
		$this->forum_appearance = $this->checkbox(tt('show in rendered forum'), $option);
		
		$option = array(3 => 3, 5 => 5, 8 => 8, 10 => 10, 15 => 15, 20 => 20);
		$this->forum_entries_number = $this->select(tt('forum entries per page'), $option);
		$this->extendBefore('forum_comment_write_label', 'forum_entries_number');
	}
}
?>
