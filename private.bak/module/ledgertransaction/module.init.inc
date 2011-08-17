<?php
function module_get_info_ledgertransaction(){
	return array(
		'name' => tt('LEDGERTRANSACTION'),
		'description' => tt('TEST')
	);
}

function module_init_ledgertransaction(){
	include_once('LedgerTransaction.class.inc');
	include_once('LedgerMovementModel.class.inc');
	include_once(INCLUDE_PATH.'class/QuickTableCreator.class.inc');

	$ledgert = new LedgerTransaction();
	$ledgert->initModule('LedgerTransaction.class.inc');

	$movementCreator = new QuickTableCreator(new LedgerMovementModel());
	$movementCreator->create();

}

function module_drop_ledgertransaction(){
	include_once('LedgerTransaction.class.inc');
	$ledgert = new LedgerTransaction();
	$ledgert->dropModule();

}
?>
