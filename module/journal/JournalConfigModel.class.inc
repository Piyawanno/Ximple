<?php
class JournalConfigModel extends ContentConfigModel{
	function JournalConfigModel(){
		ContentConfigModel::ContentConfigModel('journal');
		
		$option = array(
			'avatar' => tt('show avatar'),
			'category_icon' => tt('show category icon'),
			'comment_avatar' => tt('show avatar for comments'),
			'signature' => tt('user signature'),
			'sibling' => tt('next/previous entry'),
		);
		$this->journal_appearance = $this->checkbox(tt('show in rendered journal'), $option);
		
		$option = array(3 => 3, 5 => 5, 8 => 8, 10 => 10, 15 => 15, 20 => 20);
		$this->journal_entries_number = $this->select(tt('journal entries per page'), $option);
		$this->extendBefore('journal_comment_write_label', 'journal_entries_number');
	}
}
?>
