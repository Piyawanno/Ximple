<?php
class LocaleModuleModel extends Model{
	function LocaleModuleModel(){
		$this->module = $this->select(tt('module'), locale_get_module());
	}
}
?>
