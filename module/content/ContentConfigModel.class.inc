<?php
abstract class ContentConfigModel extends Model{
	function ContentConfigModel($mode){
		$show_avatar = $mode.'_show_avatar';
		$this->$show_avatar = $this->enable(tt('show avatar'));
		$show_category = $mode.'_show_category';
		$this->$show_category = $this->enable(tt('show category icon'));
		$comment_write_label = $mode.'_comment_write_label';
		$this->$comment_write_label = $this->title(tt('label for comment write form'));
		$comment_page_length = $mode.'_comment_page_length';
		$option = array(5 => 5, 10 => 10, 15 => 15, 20 => 20, 50 => 50);
		$this->$comment_page_length = $this->select(tt('number of shown comments per page'), $option);
		$comment_show_avatar = $mode.'_comment_show_avatar';
		$this->$comment_show_avatar = $this->enable(tt('enable avatar by comment'));
		
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
