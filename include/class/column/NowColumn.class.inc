<?php
require_once('HiddenColumn.class.inc');
class NowColumn extends HiddenColumn{
	public $isUpdateTime=false;
	public $formatDateBySelect = false;
	public $dataFormat;
	
	function NowColumn(){
		HiddenColumn::HiddenColumn(NOW, 'timestamp');
	}
	
	public function triggerUpdateForm(){
		if($this->isUpdateTime) $this->data = NOW;
	}
	
	public function triggerSelect(){
		if($this->formatDateBySelect){
			$this->data = date($this->dataFormat, strtotime($this->data));
		}
	}
}
?>
