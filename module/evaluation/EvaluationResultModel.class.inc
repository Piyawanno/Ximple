<?php
class EvaluationResultModel extends Model{
	function EvaluationResultModel(){
		$this->evaluation = $this->hidden(0, 'int');
		$this->reference = $this->hidden(0, 'int');
		$this->result = $this->hidden(0, 'int');
	}
}
?>
