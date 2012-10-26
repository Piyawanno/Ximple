<?php
execute_add_extended_class('rtna', 'classlog', 'Classlog');
include('ClasslogModel.class.inc');

class Classlog extends Control{
	function Classlog(){
		$this->moduleTitle = tt('Classlog');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'classlog';
		$this->tableName = 'rtna_classlog';
		$this->init(new ClasslogModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_classlog');
	}
}
?>
