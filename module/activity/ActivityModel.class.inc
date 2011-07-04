<?php
class ActivityModel extends ContentModel{
	function ActivityModel(){
		ContentModel::ContentModel('activity');
		$this->checkPath();
		$this->icon = $this->imageLoader(tt('icon'), 'files/activity/');
		$this->activity_date = $this->calendar(tt('activity date'));
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'activity_date');
	}
	
	private function checkPath(){
		$path  = FILES_PATH.'activity/';
		if(!is_dir($path))  mkdir($path);
	}
}
?>
