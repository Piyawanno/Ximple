<?php
execute_add_extended_class('hitdict', 'translate', 'HitDictTranslate');
require_once('HitDictTranslateModel.class.inc');

class HitDictTranslate extends Control{
	function HitDictTranslate(){
		$this->moduleName = 'hitdict';
		$this->moduleExtension = 'translate';
		$this->parentColumn = 'translate';
		$this->moduleTitle = tt('HitDict Translation');
		$this->tableName = 'hitdict_translate';
		$this->writeLabel = tt('Add new Translation to Keyword');
		
		$this->init(new HitDictTranslateModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('HitDict'), $this->moduleName);
		document_set_path($this->moduleTitle, $this->fullModuleName);
	}
	
	private function setAccess(){
	}
	
	private function setAction(){
	}
}
?>
