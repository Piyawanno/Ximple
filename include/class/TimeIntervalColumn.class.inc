<?php
class TimeIntervalColumn extends ModelColumn{
	private $interval;
	
	function TimeIntervalColumn($label, $interval, $help=null){
		$this->type = 'int';
		$this->form = 'select';
		$this->label = $label;
		$this->help = $help;
		$this->interval = $interval;
		$this->setOption();
	}
	
	public function trigerSelect(){
		$this->data = $this->formatTimeInterval($this->data);
	}
	
	private function setOption(){
		$this->option = array();
		foreach($this->interval as $second){
			$this->option[$second] = $this->formatTimeInterval($second);
		}
	}
	
	private function formatTimeInterval($second){
		if($second >= 86400){
			$format = 'z \d\a\y\s';
			if($second%86400) $format .= ' G \h\o\u\r\s';
		}elseif($second >= 3600){
			$format = 'G \h\o\u\r\s';
			if($second%3600) $format .= ' i \m\u\n\i\t\e\s';
		}elseif($second >= 60){
			$format = 'i \m\u\n\i\t\e\s';
			if($second%60) $format .= ' s \s\e\c\o\n\d\s';
		}else{
			$format = 's \s\e\c\o\n\d\s';
		}
		return date($format, $second);
	}
}
?>
