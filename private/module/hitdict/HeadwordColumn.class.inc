<?php
require_once(ROOT_PATH.'include/class/column/AutoCompleteColumn.class.inc');

class HeadwordColumn extends AutoCompleteColumn{
	function HeadwordColumn($label, $help=null){
		AutoCompleteColumn::AutoCompleteColumn($label, 'hitdict_get_headword', $help);
		$this->setType('array');
		$this->isSerialize = true;
	}
	
	public function triggerInsertForm(){
		$this->getHeadwordInputString();
	}
	
	public function triggerUpdateForm(){
		$this->getHeadwordInputString();
	}
	
	public function triggerPostInsert(){
		$this->getHeadWordID();
	}
	
	public function triggerPostUpdate(){
		$this->getHeadWordID();
	}
	
	private function getHeadWordID(){
		$headwords = input_split_comma($this->data);
		$clause = "WHERE headword='".join("' OR headword='", $headwords)."'";
		$this->data = array_keys(db_select_single_column('hitdict', 'id', $clause));
	}
	
	private function getHeadwordInputString(){
		print_r($this->data);
	}
}
?>
