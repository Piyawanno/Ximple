<?php
class DevelCardModel extends Model{
	function DevelCardModel(){
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = 'develcard_display';
		
		$this->owner = $this->owner();
		
		$this->create_date = $this->now();
		$this->create_date->label = tt('created');
		$this->create_date->isList = true;
		$this->create_date->isReachable = true;
		
		$isAdmin = authority_group('develcard_moderator');
		$isAdmin = ($isAdmin or authority_group('develcard_admin'));
		if($isAdmin) $this->initAdminColumns();
		else $this->initContributorColumns();
		
		$this->type = $this->select(tt('type'), develcard_get_type_option());
		$this->type->isList = true;
		$this->type->isReachable = true;
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isReachable = true;
		
		$this->section = $this->section();
	}
	
	private function initAdminColumns(){
		$this->deadline = $this->calendar(tt('deadline'));
		$this->deadline->isList = true;
		
		$this->priority = $this->select(tt('priority'), develcard_get_priority_option());
		$this->priority->isList = true;
		$this->priority->isReachable = true;
		$this->status = $this->select(tt('status'), $statusOption);
		
		$this->resolver = $this->user(tt('resolver'));
	}
	
	private function initContributorColumns(){
		$this->deadline = $this->now();
		$this->deadline->defaultData = time() + 60*60*24*7;
		$this->deadline->data = time() + 60*60*24*7;
		
		$this->priority = $this->hidden(2, 'int');
		$this->status->defaultData = 0;
		
		$this->resolver = $this->hidden(0, 'int');
	}
}
?>
