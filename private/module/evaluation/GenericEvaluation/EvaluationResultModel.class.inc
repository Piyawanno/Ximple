<?php
class EvaluationResultMode extends Model{
	function EvaluationResultMode(){
		$this->evaluation_map = $this->hidden(0, 'int');
		$this->evaluation_item = $this->hidden(0, 'int');
		$this->result = $this->hidden(0, 'int');
	}
}
?>
