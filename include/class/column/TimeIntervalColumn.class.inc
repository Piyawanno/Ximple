<?php
class TimeIntervalColumn extends SelectColumn{
	private $interval;
	
	function TimeIntervalColumn($label, $help=null){
		$this->setType('int');
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
			if($second%86400) $format .= ' G '.tt('\h\o\u\r\s');
		}elseif($second >= 3600){
			$format = 'G \h\o\u\r\s';
			if($second%3600) $format .= ' i '.tt('\m\i\n\u\t\e\s');
		}elseif($second >= 60){
			$format = 'i '.tt('\m\i\n\u\t\e\s');
			if($second%60) $format .= ' s '.tt('\s\e\c\o\n\d\s');
		}else{
			$format = 's '.tt('\s\e\c\o\n\d\s');
		}
		return date($format, $second);
	}
}
?>
