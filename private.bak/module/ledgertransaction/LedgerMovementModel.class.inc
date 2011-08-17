<?php
class LedgerMovementModel extends Model {
	public $moduleName = 'ledgertransaction';
        public $tableName = 'ledger_movement';
        public $dropMode = 'ledger_drop_movement';

	function LedgerMovementModel($transactionID=0){

		$ledger_transaction_status = array(1=>"submit",2=>"approve",3=>"revoke");

		$this->transaction_id	= $transactionID; 

		$column =  array('id','name');
		$clause = "where has_child=1;";
		$data = db_select('Ledger', $column, $clause);

		foreach($data as $id =>$arr){
			$option[$id]  =  $arr['name'];
		}

		$this->ledger_id	= $this->select( tt('ledger_id'), $option );
		$this->ledger_id->setType('int');

		$this->debit		= $this->char( tt('debit') ); 
		$this->debit->setType('int');

		$this->credit		= $this->char( tt('credit') );
		$this->credit->setType('int');

	}
}


?>
