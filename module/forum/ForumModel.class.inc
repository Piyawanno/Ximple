<?php
class ForumModel extends Model{
	function ForumModel(){
		$this->name = $this->title(tt('forum name'));
		$this->description = $this->plain(tt('description'));
		$this->category = $this->category('forum');
		$this->access_group = $this->group(tt('allowed group'));
		$this->position = $this->hidden(0, 'int');
		$this->comment_no = $this->hidden(0, 'int');
		$this->topic_no = $this->hidden(0, 'int');
		$this->last_topic = $this->hidden(0, 'int');
		$this->section = $this->section();
	}
}
?>
