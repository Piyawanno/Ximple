<?php
require_once('HiddenColumn.class.inc');
class NowColumn extends HiddenColumn{
	public $isUpdateTime=false;
	
	function NowColumn(){
		HiddenColumn::HiddenColumn(NOW, 'timestamp');
	}
	
	function triggerUpdateForm(){
		if($this->isUpdateTime) $this->data = NOW;
	}
}
?>
