<?php
execute_add_class('ledgertransaction','LedgerTransaction');
include "LedgerTransactionModel.class.inc";
class LedgerTransaction extends Control {
	function LedgerTransaction(){
		$this->moduleTitle = tt('LedgerTransaction');
		$this->moduleName  = tt('ledgertransaction');
		$this->tableName	= tt('Ledgertransaction');
		$this->init( new LedgerTransactionModel() );
	}
	function index(){
		
	}

}
?>
