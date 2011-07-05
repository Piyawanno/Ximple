<?php
class ActivityModel extends ContentModel{
	function ActivityModel(){
		ContentModel::ContentModel('activity');
		$this->checkPath();
		$this->icon = $this->imageLoader(tt('icon'), 'files/activity/');
		$this->start_date = $this->calendar(tt('start date'));
		$this->end_date = $this->calendar(tt('end date'));
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'start_date');
		$this->extendAfter('topic', 'end_date');
		
		$this->publish_time = $this->now();
		$this->publish_time->isUpdateTime = true;
	}
	
	private function checkPath(){
		$path  = FILES_PATH.'activity/';
		if(!is_dir($path))  mkdir($path);
	}
}
?>
