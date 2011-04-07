<?php
abstract class ContentConfigModel extends Model{
	function ContentConfigModel($mode){
		$appearance = $mode.'_appearance';
		$option = array(
			'avatar' => tt('avatar'),
			'category_icon' => tt('category icon'),
			'comment_avatar' => tt('avatar for comments'),
			'signature' => tt('user signature'),
		);
		$this->$appearance = $this->checkbox(tt('show in rendered page'), $option);
		
		$comment_write_label = $mode.'_comment_write_label';
		$this->$comment_write_label = $this->title(tt('label for comment write form'));
		
		$comment_page_length = $mode.'_comment_page_length';
		$option = array(
			5 => 5,
			10 => 10,
			15 => 15,
			20 => 20,
			30 => 30,
			40 => 40,
			50 => 50,
			60 => 60,
			70 => 70,
			80 => 80,
			90 => 90,
			100 => 100,
			110 => 110,
			120 => 120,
		);
		$this->$comment_page_length = $this->select(tt('comments per page'), $option);
		
		$option = content_get_comment_permission();
		$comment_permission = $mode.'_comment_permission';
		$this->$comment_permission = $this->checkbox(tt('available comment permission for contributor'), $option);
		
		$comment_permission_default = $mode.'_comment_permission_default';
		$this->$comment_permission_default = $this->radio(tt('default comment permission for contributor'), $option);
		
		$option = content_get_publishing_status();
		$publishing_status = $mode.'_publishing_status';
		$this->$publishing_status = $this->checkbox(tt('available publishing status for contributor'), $option);
		
		$publishing_status_default = $mode.'_publishing_status_default';
		$this->$publishing_status_default = $this->radio(tt('default publishing status for contributor'), $option);
	}
}
?>
