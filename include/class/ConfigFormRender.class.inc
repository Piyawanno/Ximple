<?php
require_once('FormModelRender.class.inc');
class ConfigFormRender extends FormModelRender{
	private $id = '';
	private $title;
	private $description;
	private $showByDefault = false;
	private $model = array();
	
	function ConfigFormRender($modelConnector, $title){
		$this->modelConnector = $modelConnector;
		$this->title = $title;
	}
	
	public function append($col){
		$this->id = $col;
		if($this->modelConnector->checkExist($col)){
			$this->modelConnector->setAsConfigForm($col);
			$modelColumn = $this->modelConnector->getColumn($col);
			$this->model[$col] = $modelColumn;
		}elseif(state_is_develop()){
			notify_add_error('Column '.$col.' does not exist and can not be set to ConfigForm. (ConfigFormRender->addColumn())');
		}
	}
	
	public function render($formMeta){
		if(count($this->model)){
			$rednerArray = array(
				'id' => $formMeta->id.'_'.$this->id,
				'form' => $this->renderFormModel($formMeta->id),
				'title' => $this->title,
				'label' => $this->modelConnector->getColumnAttribute('label'),
				'help' => $this->modelConnector->getColumnAttribute('help'),
				'not_null' => $this->modelConnector->getColumnNameByBoolean('isNotNull'),
				'show' => $this->showByDefault,
				'description' => $this->description,
			);
			return render($rednerArray, 'configform.tpl', 'render_config_form');
		}
	}
	
	public function setDescription($description){
		$this->description = $description;
	}
	
	public function setShowByDefault($showByDefault){
		$this->showByDefault = $showByDefault;
	}
	
	protected function getFormColumn(){
		return $this->model;
	}
}

?>
