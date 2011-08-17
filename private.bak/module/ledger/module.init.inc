<?php
function module_get_info_ledger(){
	return array(
		'name' => tt('LEDGER'),
		'description' => tt('TEST')
	);
}

function module_init_ledger(){
	include_once('Ledger.class.inc');
	$ledger = new Ledger();
	$ledger->initModule('Ledger.class.inc');
}

function module_drop_ledger(){
	include_once('Ledger.class.inc');
	$ledger = new Ledger();
	$ledger->dropModule();
}
?>
