<?php
execute_add_class('ledgertransaction','LedgerTransaction');
include "LedgerTransactionModel.class.inc";
class LedgerTransaction extends Control {
	function LedgerTransaction(){
		$this->moduleTitle = tt('LedgerTransaction');
		$this->moduleName  = tt('ledgertransaction');
		$this->tableName   = tt('Ledgertransaction');
		$this->init( new LedgerTransactionModel() );
	}
	function index(){
		
	}

	function setAction(){
		$this->addAction('ledger_drop_movement', 'dropLedgerMovement');
	}
	function dropLedgerMovement(){

	}
	function insert(){
		$debit	= pp('debit') ;
		$credit	= pp('credit') ;
		if( (count($debit) <= 1) || (count($credit) <= 1)  ) {
			notify_add_error(tt('number movement must >= 2'));
			return;
		}
		$sum_debit = 0;
		foreach( $debit as $i ){
			$sum_debit += $i;
		}
		$sum_credit = 0;
		foreach( $credit as $i ){
			$sum_credit += $i;
		}
		if( $sum_debit != $sum_credit ){
			notify_add_error(tt('total credit  must equal total debit '));
			return;
		}
		Control::insert();
	}
#	function list(){
#
#	}
}
?>
