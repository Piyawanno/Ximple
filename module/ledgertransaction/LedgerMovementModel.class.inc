<?php
class LedgerMovementModel extends Model {
	function LedgerMovementModel($transactionID=0){

		$ledger_transaction_status = array(1=>"submit",2=>"approve",3=>"revoke");

		$this->transaction_id	= $transactionID; 
		$this->ledger_id	= $this->hidden(null, int);

		$this->debit		= $this->char( tt('debit') ); 
		$this->debit->setType('int');

		$this->credit		= $this->char( tt('credit') );
		$this->credit->setType('int');

	}
}


?>
