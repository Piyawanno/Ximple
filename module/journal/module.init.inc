<?php
function module_get_info_journal(){
	$describe = tt('Journalging and news system for Ximple (based on Blog).');
	return array(
		'name' => tt('Journal'),
		'description' => $describe,
	);
}

function module_init_journal(){
	include_once('Journal.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$journal = new Journal();
	$journal->initModule('journal.module.inc');
	config_set('journal_entries_number', 5);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashblock_add('journal_last_post', 'journal', tt('Last posted Journals'), 'journal', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashblock_add('journal_last_commented', 'journal', tt('Last commented Journals'), 'journal', 'topic', $clause);
}

function module_drop_journal(){
	include_once('Journal.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$journal = new Journal();
	$journal->dropModule();
	notify_add_info(tt('Journal has been successfully deactivated'));
	config_drop('journal_entries_number');
	flashblock_drop('journal_last_post');
	flashblock_drop('journal_last_commented');
}
?>
