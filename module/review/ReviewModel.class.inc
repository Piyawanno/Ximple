<?php
class ReviewModel extends Model{
	function ReviewModel(){
#		$userInfo = userinfo_get_info_by_id(gg('id'));   
#		$this->reviewee = $this->hidden(gg('id'), 'int');
#		$this->reviewee = $this->title(tt('id reviewee'));
		$this->reviewee = $this->hidden(gg('id'), 'int');
		$this->reviewee->isList = true;
		$this->reviewee->isReachable = true;
		$this->reviewer = $this->owner();
		$this->reviewer->label = tt('reviewer');
		$this->reviewer->isList = true;
		$this->reviewer->isReachable = true;
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
			4 => tt('*****')
		);
		$this->star = $this->select(tt('star'), $starOption);
		$this->star->isList = true;
		$this->star->isReachable = true;
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->description->isReachable = true;
		
		$this->section = $this->section();
	}
}
?>
