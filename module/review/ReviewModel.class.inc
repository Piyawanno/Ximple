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
		$this->createdate->dateFormat = 'd/m/y H:i:s';
		$this->createdate->isList = true;
		$this->createdate->isReachable = true;

		$starOption = array(
			20 => tt('*'),
			40 => tt('**'),
			60 => tt('***'),
			80 => tt('****'),
			100 => tt('*****')
		);
		$this->star = $this->select(tt('star'), $starOption);
		$this->star->isList = true;
		$this->star->isReachable = true;
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->description->isReachable = true;
		
		$this->point1 = $this->hidden(1, 'int');
		$this->point1->isList = true;
		$this->point2 = $this->hidden(0, 'int');
		$this->point2->isList = true;
		
		$this->section = $this->section();
	}
}
?>
