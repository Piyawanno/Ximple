<?php
require_once(ROOT_PATH.'include/class/column/NoneColumn.class.inc');
class ConfigureColumn extends NoneColumn{
	function ConfigureColumn(){
		$this->setType('array');
		$this->defaultData = directory_default_configuration();
	}
	
	public function triggerPreUpdate(){
		$this->isDB = false;
	}
}
?>
