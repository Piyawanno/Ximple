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
		document_set_redirection('evaluation_manage/model/'.pp('model'));
	}
	
	public function update(){
	
	}
	
	public function drop(){
		execute_set_db();
		$clause = 'WHERE evaluatee='.gg('evaluatee')." AND model='".gg('model')."'";
		db_drop_many($this->tableName, $caluse);
		document_set_redirection('evaluation_manage/model/'.pp('model'));
	}
	
	public function manage(){
		$this->setManagePath();
		$model = gg('model');
		if(evaluation_check_model_exists($model)){
			return $this->renderMapList($model);
		}else{
			return $this->renderManageList();
		}
	}
	
	private function renderMapList($model){
		$clause = "WHERE model='$model' GROUP BY evaluatee";
		$this->selectListPage(20, $clause);
		$this->listMeta->title = sprintf(tt('List of mapped %s'), $this->moduleTitle);
		$this->listMeta->mode = $this->moduleName;
		$this->listMeta->addOperation('evaluation_edit', tt('edit'), 'edit.png', 'model/'.$model);
		$this->setListWriteIcon(tt('Map evaluatee to evaluators'), 'evaluation_write/model/'.$model);
		$this->setListDropIcon();
		return $this->renderListPage();
	}
	
	private function renderManageList(){
		$renderArray = array('data' => evaluation_get_model_name());
		return render($renderArray, 'evaluation_manage.tpl', 'evaluation_manage');
	}
	
	private function setManagePath(){
		document_set_path(tt('Manage'), 'evaluation_manage');
		$model = gg('model');
		if(evaluation_check_model_exists($model)){
			$modelName = evaluation_get_model_name();
			document_set_path($modelName[$model], 'evaluation_manage/model/'.$model);
		}
	}
	
	private function setAccess(){
		$this->setAdmin('evaluation_admin');
		
		$this->addAction('evaluation_manage', 'manage');
		
		$this->addAccessMethod('guest', 'index');
	}
}
?>
