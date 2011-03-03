<?php
class ForumModel extends Model{
	function ForumModel(){
		$this->name = $this->title(tt('forum name'));
		$this->category = $this->category('forum');
		$this->description = $this->plain(tt('description'));
		$help = tt('Check guest to allow everyone.');
		$this->writable_group = $this->group(tt('writable group'), $help);
		$this->readable_group = $this->group(tt('readable group'), $help);
		$this->publishable_group = $this->group(tt('publishable group'), $help);
		$this->position = $this->hidden(0, 'int');
		$this->last_posted = $this->hidden(0, 'int');
		$this->last_commented = $this->hidden(0, 'int');
		$this->section = $this->section();
	}
}
?>
