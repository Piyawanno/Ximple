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
		$this->$comment_page_length = $this->spin(tt('comments per page'), 5, 50);
		
		$option = $this->getCommentPermission();
		$comment_permission = $mode.'_comment_permission';
		$this->$comment_permission = $this->checkbox(tt('available comment permission for contributor'), $option);
		
		$comment_permission_default = $mode.'_comment_permission_default';
		$this->$comment_permission_default = $this->radio(tt('default comment permission for contributor'), $option);
		
		$option = $this->getPublishingStatus();
		$publishing_status = $mode.'_publishing_status';
		$this->$publishing_status = $this->checkbox(tt('available publishing status for contributor'), $option);
		
		$publishing_status_default = $mode.'_publishing_status_default';
		$this->$publishing_status_default = $this->radio(tt('default publishing status for contributor'), $option);
	}
	
	public function getCommentPermission(){
		return content_get_comment_permission();
	}
	
	public function getPublishingStatus(){
		return content_get_publishing_status();
	}
}
?>
