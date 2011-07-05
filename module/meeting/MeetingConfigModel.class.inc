<?php
class MeetingConfigModel extends ContentConfigModel{
	function MeetingConfigModel(){
		ContentConfigModel::ContentConfigModel('meeting');
		$option = array(
			'avatar' => tt('show avatar'),
			'category_icon' => tt('show category icon'),
			'comment_avatar' => tt('show avatar for comments'),
			'signature' => tt('user signature'),
		);
		$this->meeting_appearance = $this->checkbox(tt('show in rendered meeting'), $option);
	}
}
?>
