<?php
class ActivityConfigModel extends ContentConfigModel{
	function ActivityConfigModel(){
		ContentConfigModel::ContentConfigModel('activity');
		$option = array(
			'avatar' => tt('show avatar'),
			'category_icon' => tt('show category icon'),
			'comment_avatar' => tt('show avatar for comments'),
			'signature' => tt('user signature'),
		);
		$this->activity_appearance = $this->checkbox(tt('show in rendered activity'), $option);
	}
}
?>
