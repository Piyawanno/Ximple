<?php
require_once('evaluation.tool.inc');
class EvaluationModel extends Model{
	function EvaluationModel(){
		if(evaluation_check_model_exists(gg('model'))){
			$this->model = $this->hidden(gg('model'), 'char');
		}else{
			$modelArray = evaluation_get_model_name();
			$this->model = $this->select(tt('evaluation model'), $modelArray);
		}
		$option = userinfo_get_login_name_by_role('evaluation_evaluatee');
		$this->evaluatee = $this->select(tt('evaluatee'), $option);
		$this->evaluatee->isList = true;
		$this->evaluatee->isReachable = true;
		$this->evaluatee->isOrderable = false;
		$this->evaluatee->isUser = true;
		$this->evaluatee->listMode = 'evaluation';
		$this->evaluatee->type = 'int';
		
		$option = userinfo_get_login_name_by_role('evaluation_evaluator');
		$this->evaluator = $this->checkBox(tt('evaluator'), $option);
		$this->evaluator->type = 'int';
		$this->evaluator->isReachable = true;
		$this->evaluator->isUser = true;
		
		$this->opinion = $this->hidden('', 'text');
		$this->status = $this->hidden(0, 'int');
		$this->section = $this->section();
	}
}
?>
