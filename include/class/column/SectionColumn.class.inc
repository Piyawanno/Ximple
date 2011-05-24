<?php
require_once('HiddenColumn.class.inc');
class SectionColumn extends HiddenColumn{
	function SectionColumn(){
		$this->setType('int');
		$this->isNotNull = true;
		$this->defaultData = SECTION;
		$this->data = SECTION;
	}
}
?>
