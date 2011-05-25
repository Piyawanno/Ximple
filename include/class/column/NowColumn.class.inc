<?php
require_once('HiddenColumn.class.inc');
class NowColumn extends HiddenColumn{
	public $isUpdateTime=false;
	public $formatDateBySelect = false;
	public $dateFormat;
	
	function NowColumn(){
		HiddenColumn::HiddenColumn(NOW, 'timestamp');
		$this->dateFormat = 'Y-m-d H:i:s';
	}
	
	public function triggerUpdateForm(){
		if($this->isUpdateTime) $this->data = NOW;
	}
	
	public function triggerSelect(){
		if($this->formatDateBySelect){
			$this->data = date($this->dateFormat, strtotime($this->data));
		}
	}
}
?>
