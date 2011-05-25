<?php
require_once(ROOT_PATH.'include/class/column/HiddenColumn.class.inc');

class BlockPositionColumn extends HiddenColumn{
	function BlockPositionColumn(){
		HiddenColumn::HiddenColumn('disabled', 'char');
	}
	
	function triggerInsertForm(){
		$position = gg('position');
		if(isset($position) and array_key_exists($position, cc('block_position'))){
			$this->defaultData = $position;
		}else{
			$this->defaultData = 'disabled';
		}
	}
}
?>
