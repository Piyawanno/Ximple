<?php
class ForumModel extends Model{
	function ForumModel(){
		$this->name = $this->title(tt('forum name'));
		$this->category = $this->category('forum');
		$this->description = $this->plain(tt('description'));
		$help = tt('Check guest to allowe everyone.');
		$this->allowed_group = $this->group(tt('allowed group'), $help);
		$this->position = $this->hidden(0, 'int');
		$this->comment_no = $this->hidden(0, 'int');
		$this->topic_no = $this->hidden(0, 'int');
		$this->last_posted = $this->hidden(0, 'int');
		$this->last_commented = $this->hidden(0, 'int');
		$this->section = $this->section();
	}
}
?>
