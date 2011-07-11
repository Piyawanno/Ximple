<?php
require_once('FormModelRender.class.inc');
class ConfigFormRender extends FormModelRender{
	private $id = '';
	private $title;
	private $description;
	private $showByDefault = false;
	private $model = array();
	
	function ConfigFormRender($title, $modelConnector, $description=null){
		$this->title = $title;
		$this->modelConnector = $modelConnector;
		$this->description = $this->description;
	}
	
	public function append($col){
		$this->id = $col;
		if($this->modelConnector->checkExist($col)){
			$modelColumn = $this->modelConnector->getColumn($col);
			if($modelColumn->isConfigFormAllowed){
				$this->modelConnector->setAsConfigForm($col);
				$this->model[$col] = $modelColumn;
			}
		}elseif(state_is_develop()){
			notify_add_error('Column '.$col.' does not exist and can not be set to ConfigForm. (ConfigFormRender->addColumn())');
		}
	}
	
	public function appendModel($name, $modelColumn){
		$this->model[$name] = $modelColumn;
		$this->modelConnector->addModel($name, $modelColumn);
		$this->modelConnector->setAsConfigForm($name);
	}
	
	public function render($formMeta){
		if(count($this->model)){
			$renderArray = array(
				'id' => $formMeta->id.'_'.$this->id,
				'form' => $this->renderFormModel($formMeta->id),
				'title' => $this->title,
				'label' => $this->modelConnector->getColumnAttribute('label'),
				'help' => $this->modelConnector->getColumnAttribute('help'),
				'not_null' => $this->modelConnector->getColumnNameByBoolean('isNotNull'),
				'show' => $this->showByDefault,
				'description' => $this->description,
			);
			$renderArray['rendered_form'] = render($renderArray, 'config_form.tpl', 'config_form');
			return render($renderArray, 'config_form_frame.tpl', 'config_form_frame');
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
