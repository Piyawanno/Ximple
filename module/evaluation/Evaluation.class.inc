<?php
execute_add_class('evaluation', 'Evaluation');
include('EvaluationModel.class.inc');

class Evaluation extends Control{
	function Evaluation(){
		$this->moduleTitle = tt('Evaluation');
		$this->moduleName = 'evaluation';
		$this->tableName = 'evaluation';
		$this-> setAccess();
		$this->init(new EvaluationModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		$this->setReportPath();
		$this->id = (int) gg('id');
		$model = gg('model');
		if($this->id){
			return $this->renderReport();
		}elseif(evaluation_check_model_exists($model)){
			return $this->renderReportList($model);
		}else{
			return $this->renderReportSummary();
		}
	}
	
	public function manage(){
		$this->setManagePath();
		$model = gg('model');
		if(evaluation_check_model_exists($model)){
			return $this->renderManageList($model);
		}else{
			return $this->renderManageSummary();
		}
	}
	
	public function fill(){
		$this->setFillPath();
		$model = gg('model');
		if(evaluation_check_model_exists($model)){
			return $this->renderFillForm($model);
		}else{
			return $this->renderFillSummary();
		}
	}
	
	public function write(){
		$this->setManagePath();
		return Control::write();
	}
	
	public function edit(){
		$model = $this->dataByID['model'];
		$caluse = 'WHERE evaluatee='.$this->dataByID['evaluatee']." AND model='".$model."' AND section=".SECTION;
		$this->dataByID['evaluator'] = db_select_single_column($this->tableName, 'evaluator', $caluse);
		$this->data[$this->id] = $this->dataByID;
		$this->setManagePath();
		return Control::edit();
	}
	
	public function insert(){
		execute_set_db();
		if(evaluation_check_model_exists(pp('model'))){
			$this->insertData();
		}
		document_set_redirect('evaluation_manage/model/'.pp('model'));
	}
	
	public function update(){
		execute_set_db();
		if(evaluation_check_model_exists(pp('model'))){
			$this->dropByUpdate(pp('model'));
			$this->insertData();
		}
		document_set_redirect('evaluation_manage/model/'.pp('model'));
	}
	
	public function drop(){
		execute_set_db();
		$this->id = (int) gg('id');
		$this->selectByID($this->column, true);
		$clause = 'WHERE evaluatee='.$this->dataByID['evaluatee']." AND model='".$this->dataByID['model']."'";
		$this->dropByClause($clause);
		document_set_redirect('evaluation_manage/model/'.$this->dataByID['model']);
	}
	
	private function renderReportList($model){
		$this->listMeta->title = tt('List of Evaluation Report');
		$this->setReportListColumn();
		$this->listMeta->mode = 'evaluation';
		$this->listMeta->addParameter('model', $model);
		$this->listMeta->groupBy = 'evaluatee';
		$this->selectListPage(20, "WHERE model='$model'", array('status'), true);
		$this->checkEvaluatorNumber($model);
		$this->averageResult($model);
		$this->postSelect();
		return $this->renderListPage();
	}
	
	private function renderManageList($model){
		$this->listMeta->mode = 'evaluation_manage';
		$this->listMeta->addParameter('model', $model);
		$this->listMeta->groupBy = 'evaluatee';
		$this->listMeta->title = tt('List of mapped Evaluations');
		$this->listMeta->addOperation('evaluation_edit', tt('edit'), 'edit.png', 'model/'.$model);
		$this->setListWriteIcon(tt('Map evaluatee to evaluators'), 'evaluation_write/model/'.$model);
		$this->setListDropIcon();
		$this->selectListPage(20, "WHERE model='$model'");
		return $this->renderListPage();
	}
	
	private function renderManageSummary(){
		$renderArray = array('data' => evaluation_get_model());
		return render($renderArray, 'evaluation_manage.tpl', 'evaluation_manage');
	}
	
	private function renderReportSummary(){
		$renderArray = array('data' => evaluation_get_model());
		return render($renderArray, 'evaluation_report.tpl', 'evaluation_report');
	}
	
	private function renderFillSummary(){
		$renderArray = array('data' => evaluation_get_model());
		return render($renderArray, 'evaluation_fill.tpl', 'evaluation_fill');
	}
	
	private function renderReport(){
		$this->id = (int) gg('id');
		$this->selectByID($this->column, true);
		$model = $this->dataByID['model'];
		$evaluatee = userinfo_get_info_by_id($this->dataByID['evaluatee']);
		$modelDescription = evaluation_get_model();
		$result = $this->getReportData($model);
		$profile_access = authority_group('evaluation_evaluator');
		$profile_access = ($profile_access or authority_group('evaluation_admin'));
		$renderArray = array(
			'data' => $this->data,
			'model' => $modelDescription[$model],
			'result' => $result,
			'profile_access' => $profile_access,
			'evaluatee' => $evaluatee,
		);
		document_set_path($modelDescription[$model]['name'], 'evaluation/model/'.$model);
		document_set_path($evaluatee['login_name']);
		head_add_css('list.css');
		return render($renderArray, 'evaluation.tpl', 'evaluation');
	}
	
	private function setManagePath(){
		document_set_path(tt('Manage'), 'evaluation_manage');
		$model = gg('model');
		if(evaluation_check_model_exists($model)){
			$modelName = evaluation_get_model_name();
			document_set_path($modelName[$model], 'evaluation_manage/model/'.$model);
		}
	}
	
	private function setReportPath(){
		$model = gg('model');
		if(evaluation_check_model_exists($model)){
			$modelName = evaluation_get_model_name();
			document_set_path($modelName[$model], 'evaluation/model/'.$model);
		}
	}
	
	private function setFillPath(){
		$model = gg('model');
		document_set_path(tt('Fill Form'), 'evaluation_fill');
		if(evaluation_check_model_exists($model)){
			$modelName = evaluation_get_model_name();
			document_set_path($modelName[$model], 'evaluation_fill/model/'.$model);
		}
	}
	
	private function setAccess(){
		$this->setAdmin('evaluation_admin');
		$this->addAction('evaluation_manage', 'manage');
		$this->addAction('evaluation_fill', 'fill');
		$this->addAction('evaluation_save', 'save');
		
		$this->addAccessMethod('evaluation_evaluator', 'index');
		$this->addAccessMethod('evaluation_evaluator', 'fill');
		$this->addAccessMethod('evaluation_evaluator', 'save');
		
		$this->addAccessMethod('evaluation_evaluatee', 'index');
	}
	
	private function dropByUpdate($model){
		$clause = "WHERE model='$model' AND SECTION=".SECTION." AND evaluatee=".pp('evaluatee').' AND ';
		$clause.= "(evaluator=".join(' OR evaluator=', pp('evaluator')).')';
		$this->dropByClause($clause);
	}
	
	private function dropByClause($clause){
		$evaluationID = db_select_single_column('evaluation', 'id', $clause);
		foreach($evaluationID as $key=>$value){
			db_drop('evaluation', $value);
		}
		if(count($evaluationID)){
			db_drop_many('evaluationresult', 'evaluation='.join(' OR evaluation=', $evaluationID));
		}
	}
	
	private function insertData(){
		$dataArray = array(
			'evaluatee' => pp('evaluatee'),
			'model' => pp('model'),
			'section' => SECTION,
		);
		foreach(pp('evaluator') as $key => $valuator){
			$dataArray['evaluator'] = $valuator;
			db_insert($this->tableName, $dataArray);
		}
	}
	
	private function setReportListColumn(){
		$average = Model::spin(tt('averaged'), 0, 100);
		$average->isList = true;
		$average->isDB = false;
		$average->isOrderable = false;
		$this->modelConnector->addModel('average', $average);
		$number = Model::char(tt('all/finish/draft'));
		$number->isList = true;
		$number->isDB = false;
		$number->isOrderable = false;
		$this->modelConnector->addModel('number', $number);
	}
	
	private function checkEvaluatorNumber($model){
		$related = $this->getRelated($model);
		$status = $this->getStatus($related);
		$this->renderEvaluatorNumber($status);
	}
	
	private function averageResult($model){
		$related = $this->getRelated($model);
		$result = $this->getResult(array_keys($related));
		$result = $this->averageRowWise($result, $related);
		foreach($this->data as $key => $value){
			if(isset($result[$value['evaluatee']])){
				$this->data[$key]['average'] = $result[$value['evaluatee']];
			}else{
				$this->data[$key]['average'] = 0;
			}
		}
	}
	
	private function getRelated($model){
		if(count($this->data)){
			$evaluatee = array();
			foreach($this->data as $key => $value){
				$evaluatee[] = $value['evaluatee'];
			}
			$clause = "WHERE model='$model' AND section=".SECTION.' AND ';
			$clause.= '(evaluatee='.join(' OR evaluatee=', $evaluatee).')';
			return db_select_single_column('evaluation', 'evaluatee', $clause);
		}else{
			return array();
		}
	}
	
	private function getResult($relatedID){
		$clause = 'WHERE evaluation='.join(' OR evaluation=', $relatedID);
		$column = array('evaluation', 'reference', 'result');
		$dbResult = db_select('evaluationresult', $column, $clause);
		$result = array();
		foreach($dbResult as $key => $value){
			$result[$value['evaluation']][$value['reference']] = $value['result'];
		}
		return $result;
	}
	
	private function getStatus($related){
		if(count($related)){
			$clause = 'WHERE id='.join(' OR id=', array_keys($related));
			$statusDB = db_select('evaluation', array('status', 'evaluatee'), $clause);
			$status = array();
			foreach($statusDB as $key => $value){
				$evaluatee = $value['evaluatee'];
				
				if(isset($status[$evaluatee])) $status[$evaluatee]['all'] += 1;
				else $status[$evaluatee] = array('all' => 1);
				
				if($value['status'] == 1) $status[$evaluatee]['draft'] += 1;
				if($value['status'] == 2) $status[$evaluatee]['finish'] += 1;
			}
			return $status;
		}else{
			return array();
		}
	}
	
	private function averageRowWise($result, $related){
		$sum = array();
		$count = array();
		$averaged = array();
		foreach($result as $evaluation => $reference){
			$evaluatee = $related[$evaluation];
			foreach($reference as $key => $value){
				$sum[$evaluatee][$key] += $value;
				$count[$evaluatee][$key] += 1;
			}
		}
		
		foreach($sum as $evaluatee => $reference){
			foreach($reference as $key => $value){
				$averaged[$evaluatee] += $value/$count[$evaluatee][$key];
			}
		}
		return $averaged;
	}
	
	private function renderEvaluatorNumber($status){
		foreach($this->data as $key => $value){
			if(isset($status[$value['evaluatee']])){
				$result  = $status[$value['evaluatee']];
				$number  = $result['all'].'/';
				$number .= isset($result['finish']) ? $result['finish'].'/' : '0/';
				$number .= isset($result['draft'])  ? $result['draft'].'/'  : '0/';
				$this->data[$key]['number'] = $number;
			}else{
				$this->data[$key]['number'] = '0/0/0';
			}
		}
	}
	
	private function checkResultPermission($result){
		if(authority_group('evaluation_evaluator')){
			foreach($result as $key => $value){
				if($this->data[$key]['evaluator'] != USER_ID){
					unset($result[$key]);
					unset($this->data[$key]);
				}
			}
		}
		return $result;
	}
	
	private function getReportData($model){
		$related = $this->getRelated($model);
		$clause = 'WHERE (id='.join(' OR id=', array_keys($related)).') AND status=2';
		$this->select($this->column, $clause, true);
		$result = $this->getResult(array_keys($related));
		$result = $this->checkResultPermission($result);
		$this->data = userinfo_get_info($this->data, 'evaluator');
		$this->data = userinfo_get_info($this->data, 'evaluatee');
		return $result;
	}
}
?>
