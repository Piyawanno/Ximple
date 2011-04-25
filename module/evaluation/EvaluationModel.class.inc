<?php
require('EvaluateeColumn.class.inc');
require('EvaluatorColumn.class.inc');
require_once('evaluation.tool.inc');

class EvaluationModel extends Model{
	function EvaluationModel(){
		$this->model = $this->select(tt('evaluation model'), evaluation_get_model_name());
		$this->evaluatee = new EvaluateeColumn();
		$this->evaluator = new EvaluatorColumn();
		$this->opinion = $this->hidden('', 'text');
		$this->status = $this->hidden(0, 'int');
	}
}
?>
