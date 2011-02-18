<?php
class SeminarModel extends Model{
	function SeminarModel(){
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = 'seminar_display';

		$this->location = $this->title(tt('location'));
		
		$this->owner = $this->owner();

		$this->createdate = $this->now();
		$this->createdate->label = tt('created');
		$this->createdate->dateFormat = 'd/m/y';
		$this->createdate->isList = true;
		$this->createdate->isReachable = true;

		$this->classdate->defaultData = date('Y-m-d H:i:s', time()+60*60*24*7);
		$this->classdate->data = date('Y-m-d H:i:s', time()+60*60*24*7);
		$this->classdate = $this->calendar(tt('Date'));
		$this->classdate->isList = true;
		$this->classdate->isReachable = true;
//		$this->classdate = $this->now();
		
		$timeOption = array(
			0 => tt('00:00'),
			1 => tt('00:30'),
			2 => tt('01:30'),
			3 => tt('01:30'),
			4 => tt('02:00'),
			5 => tt('02:30'),
			6 => tt('03:00'),
			7 => tt('03:30'),
			8 => tt('04:00'),
			9 => tt('04:30'),
			10 => tt('05:00'),
			11 => tt('05:30'),
			12 => tt('06:00'),
			13 => tt('06:30'),
			14 => tt('07:00'),
			15 => tt('08:30'),
			16 => tt('09:00'),
			17 => tt('09:30'),
			18 => tt('10:00'),
			19 => tt('10:30'),
			20 => tt('11:00'),
			21 => tt('11:30'),
			22 => tt('12:00'),
			23 => tt('12:30'),
			);
		$this->classtime = $this->select(tt('time'), $timeOption);
		
		$this->duration = $this->title(tt('duration'));
		
		$this->size = $this->title(tt('size'));
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isReachable = true;
		
		$this->section = $this->section();
	}
}
?>
