<?php
class ReviewModel extends Model{
	function ReviewModel(){
		$this->toid = $this->users(tt('To ID'));
		$this->toid->isReachable = true;
		$this->owner = $this->owner();
		$this->owner->isReachable = true;
		$this->createdate = $this->now();
		$this->createdate->label = tt('created');
		$this->createdate->dateFormat = 'd/m/y';
		$this->createdate->isList = true;
		$this->createdate->isReachable = true;

		$starOption = array(
			0 => tt('*'),
			1 => tt('**'),
			2 => tt('***'),
			3 => tt('****'),
			4 => tt('*****'),
		);
		$this->star = $this->select(tt('star'), $starOption);
		$this->star->isReachable = true;
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isReachable = true;
		
		$this->section = $this->section();
	}
}
?>
