<?php
class DevelCardModel extends Model{
	function DevelCardModel(){
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = 'develcard_display';
		$this->owner = $this->owner();
		$this->createdate = $this->now();
		$this->createdate->isList = true;
		$this->createdate->isReachable = true;
		
		$typeOption = array(
			0 => tt('bug'),
			1 => tt('enhancement'),
			2 => tt('suggestions'),
			3 => tt('document'),
		);
		$priorityOption = array(
			0 => tt('0 - High'),
			1 => tt('1 - Medium'),
			2 => tt('2 - Low'),
			3 => tt('3 - No-Effect'),
		);
		
		$statusOption = array(
			0 => tt('created'),
			1 => tt('in progress'),
			2 => tt('closed'),
			);
		$this->status = $this->select(tt('status'), $statusOption);
			
		if(authority_group('develcard_moderator') or authority_group('develcard_admin')){
			$this->deadline = $this->calendar(tt('deadline'));
			$this->deadline->isList = true;
			$this->priority = $this->select(tt('priority'), $priorityOption);
			$this->priority->isList = true;
			$this->priority->isReachable = true;
			$this->status = $this->select(tt('status'), $statusOption);
			$this->resolver = $this->user(tt('resolver'));
			$this->type = $this->select(tt('type'), $typeOption);
		}else{
			$this->status->defaultData = 0;
			$this->deadline = $this->now();
			$this->deadline->defaultData = 'now + 7';
			$this->deadline->data = 'now + 7';
			$this->priority = $this->hidden(2, 'int');
		}
		$this->type = $this->select(tt('type'), $typeOption);
		$this->type->isList = true;
		$this->type->isReachable = true;
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isReachable = true;
		
		$this->section = $this->section();
	}
}
?>
