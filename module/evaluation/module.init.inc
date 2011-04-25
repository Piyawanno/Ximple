<?php
function module_get_info_evaluation(){
	$describe = tt('Simple Evaluation for internal managment in RTNA.');
	return array(
		'name' => tt('Evaluation'),
		'description' => $describe,
	);
}

function module_init_evaluation(){
	include_once('Evaluation.class.inc');
	include_once('EvaluationResultModel.class.inc');
	include_once(ROOT_PATH.'include/class/QuickTableCreator.class.inc');
	$evaluation = new Evaluation();
	$evaluation->initModule('Evaluation.class.inc');
	$tableCreator = new QuickTableCreator('evaluationresult', new EvaluationResultModel());
	$tableCreator->create();
	
	module_add_role('evaluation_admin', 'Evaluation Administrator', 'Who can map evaluator to evaluatee and get report.');
	module_add_role('evaluation_evaluator', 'Evaluatior', 'Who can fill evaluation form.');
	module_add_role('evaluation_evaluatee', 'Evaluatiee', 'Who must be evaluated.');
	
	module_add_panel('Evaluation', 'evaluation_admin', 'evaluation_manage', 'manage Evaluation');
	module_add_panel('Evaluation', 'evaluation_admin', 'evaluation_report', 'report Evaluation');
	module_add_panel('Evaluation', 'evaluation_admin', 'evaluation_fill', 'fill Evaluation');
	module_add_panel('Evaluation', 'evaluation_evaluator', 'evaluation_fill', 'fill Evaluation');
	module_add_panel('Evaluation', 'evaluation_evaluatee', 'evaluation_report', 'report Evaluation');
}

function module_drop_evaluation(){
	include_once('Evaluation.class.inc');
	$evaluation = new Evaluation();
	$evaluation->dropModule();
	module_drop_role('evaluation_admin');
	module_drop_role('evaluation_evaluator');
	module_drop_role('evaluation_evaluatee');
	module_drop_panel('Evaluation');
}
?>
