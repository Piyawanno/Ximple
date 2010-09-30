<?php
class VideoConfigModel extends ContentConfigModel{
	function VideoConfigModel(){
		ContentConfigModel::ContentConfigModel('video');
		$this->video_width = $this->char(tt('player width'));
		$this->video_width->isNotNull = true;
		$this->video_height = $this->char(tt('player height'));
		$this->video_height->isNotNull = true;
		$option = array(3 => 3, 5 => 5, 8 => 8, 10 => 10, 15 => 15, 20 => 20);
		$this->video_entries_number = $this->select(tt('number of shown video entries per page'), $option);
		$this->extendBefore('video_show_avatar', 'video_width');
		$this->extendBefore('video_show_avatar', 'video_height');
		$this->extendBefore('video_comment_write_label', 'video_entries_number');
	}
}
?>
