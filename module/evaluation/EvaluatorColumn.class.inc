<?php
class EvaluatorColumn extends ModelColumn{
	function EvaluatorColumn(){
		$this->type = 'int';
		$this->form = 'checkbox';
		$this->label = tt('evaluator');
		$this->option = array();	
	}
	
	public function triggerInsertForm(){
		$this->getSelection();
	}
	
	public function triggerUpdateForm(){
		$this->getSelection();
	}
	
	private function getSelection(){
		
	}
}
?>
