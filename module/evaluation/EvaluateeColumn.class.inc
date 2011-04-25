<?php
class EvaluateeColumn extends ModelColumn{
	function EvaluateeColumn(){
		$this->type = 'int';
		$this->form = 'select';
		$this->label = tt('evaluatee');
		$this->option = array();	
	}
	
	public function triggerInsertForm(){
		$this->getSelection();
	}
	
	public function triggerUpdateForm(){
		$this->getSelection();
	}
	
	private function getSelection(){
		$uid = userinfo_get_uid_by_role('evaluation_evaluatee');
	}
}
?>
