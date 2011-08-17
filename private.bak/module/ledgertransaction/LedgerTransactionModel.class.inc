<?php

class LedgerTransactionModel extends Model {
	function LedgerTransactionModel(){
		include_once "LedgerMovementModel.class.inc";

		$ledger_transaction_status = array(1=>"submit",2=>"approve",3=>"revoke");

		$this->datetime		= $this->timeStamp( tt('transaction_time') );
		$this->description	= $this->shortText( tt('description') );
		$this->status		= $this->select( tt('Transaction_status') , $ledger_transaction_status );
		$this->status->setType('int');
		$this->section          = $this->section();

		$this->movement = $this->grid(tt('movement'))->setModel(new LedgerMovementModel());
	}
}
?>
