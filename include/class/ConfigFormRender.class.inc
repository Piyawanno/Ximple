<?php

class ConfigFormRender{
	private $id = '';
	private $title;
	private $modelConnector;
	private $description;
	private $model = array();
	
	function ConfigFormRender($modelConnector, $title, $description){
		$this->modelConnector = $modelConnector;
		$this->title = $title;
		$this->description = $description;
	}
	
	public function append($col){
		$this->id = $col;
		if($this->modelConnector->checkExist($col)){
			$this->modelConnector->setAsConfigForm($col);
			$this->model[$col] = $this->modelConnector->getColumn($col);
		}elseif(state_is_develop()){
			notify_add_error('Column '.$col.' does not exist and can not be set to ConfigForm. (ConfigFormRender->addColumn())');
		}
	}
	
	public function render($formMeta){
		$rednerArray = array(
			'id' => $formMeta->id.'_'.$this->id,
			'form' => form($formMeta->id, $this->model),
			'title' => $this->title,
			'label' => $this->modelConnector->getColumnAttribute('label'),
			'help' => $this->modelConnector->getColumnAttribute('help'),
			'not_null' => $this->modelConnector->getColumnNameByBoolean('isNotNull'),
			'description' => $this->description,
		);
		return render($rednerArray, 'configform.tpl', 'render_config_form');
	}
}

?>
