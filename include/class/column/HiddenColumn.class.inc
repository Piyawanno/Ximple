<?php
require_once('CharColumn.class.inc');
class HiddenColumn extends CharColumn{
	function HiddenColumn($default, $type){
		$this->setType($type);
		$this->defaultData = $default;
		$this->data = $default;
		$this->setFormAtrribute('type', 'hidden');
	}
}
?>
