<?php
execute_add_class('evaluation', 'Evaluation');
include('EvaluationModel.class.inc');

class Evaluation extends Control{
	function Evaluation(){
		$this->moduleTitle = tt('Evaluation');
		$this->moduleName = 'evaluation';
		$this->tableName = 'evaluation';
		$this->setAdmin('evaluation_admin');
		$this->init(new EvaluationModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	function index(){
	
	}
}
?>
