<?php
class MeetingModel extends ContentModel{
	function MeetingModel(){
		ContentModel::ContentModel('meeting');
		$this->checkPath();
		$this->icon = $this->imageLoader(tt('icon'), 'files/meeting/');
		
		$this->meeting_date = $this->timeStamp(tt('meeting date time'));
		$this->meeting_date->dateFormat = 'Y-m-d H:i:s';
		
		$this->meeting_period = $this->timeInterval(tt('meeting period'));
		$this->meeting_period->defaultData = 7200;
		$this->meeting_period->isDay = false;
		$this->meeting_period->isSecond = false;
		
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'meeting_date');
		$this->extendAfter('topic', 'meeting_period');
		
		$this->paricipant_group = $this->group('');
		$this->paricipant_group->defaultData = cc('meeting_default_group');
		$this->paricipant_group->isExceptedGuest = true;
		$this->paricipant_group->isExceptedAdmin = false;
		
		$this->publish_time = $this->now();
		$this->publish_time->isUpdateTime = true;
	}
	
	private function checkPath(){
		$path  = FILES_PATH.'meeting/';
		if(!is_dir($path))  mkdir($path);
	}
}
?>
