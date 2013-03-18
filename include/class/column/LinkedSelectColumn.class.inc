<?php
require_once('SelectColumn.class.inc');
class LinkedSelectColumn extends SelectColumn{
	function LinkedSelectColumn($label, $option, $help=null){
		SelectColumn::SelectColumn($label, $option, $help);
		$this->setType('int');
	}
}
?>
