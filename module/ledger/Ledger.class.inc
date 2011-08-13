<?php
execute_add_class('ledger','Ledger');
include "LedgerModel.class.inc";
class Ledger extends Control {
	function Ledger(){
		$this->moduleTitle = tt('Ledger');
		$this->moduleName  = tt('ledger');
		$this->tableName	= tt('Ledger');
		$this->init( new LedgerModel() );

	}
	function index(){
		
	}

}
?>
