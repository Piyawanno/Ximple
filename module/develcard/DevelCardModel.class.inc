<?php
class DevelCardModel extends Model{
	function DevelCardModel(){
		$this->topic = $this->title(tt('topic'));
		$this->createdate = $this->now();
		if(authority_group('develcard_moderator') or authority_group('develcard_admin')){
			$this->deadline = $this->calendar(tt('deadline'));
			$priorityOption = array(
				0 => tt('0 - High'),
				1 => tt('1 - Medium'),
				2 => tt('2 - Low'),
				3 => tt('3 - No-Effect'),
			);
			$this->priority = $this->select(tt('priority'), $priorityOption);
			
		}else{
			$this->deadline = $this->now();
			$this->deadline->defaultData = 'now + 7';
			$this->deadline->data = 'now + 7';
			$this->priority = $this->hidden(2, 'int');
		}
		$typeOption = array(
			0 => tt('bug'),
			1 => tt('enhancement'),
			2 => tt('suggestions'),
			3 => tt('document'),
		);		
		$this->type = $this->select(tt('type'), $typeOption);
		
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isReachable = true;
		$this->resolver = $this->user(tt('resolver'));
		$this->section = $this->section();
	}
}
?>
