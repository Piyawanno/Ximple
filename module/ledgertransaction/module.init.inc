<?php
function module_get_info_ledgertransaction(){
	return array(
		'name' => tt('LEDGERTRANSACTION'),
		'description' => tt('TEST')
	);
}

function module_init_ledgertransaction(){
	include_once('LedgerTransaction.class.inc');
	$ledgert = new LedgerTransaction();
	$ledgert->initModule('LedgerTransaction.class.inc');
}

function module_drop_ledgertransaction(){
	include_once('LedgerTransaction.class.inc');
	$ledgert = new LedgerTransaction();
	$ledgert->dropModule();
}
?>
