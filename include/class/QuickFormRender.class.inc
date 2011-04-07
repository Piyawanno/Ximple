<?php

require_once(ROOT_PATH.'include/tool/form.tool.inc');

class QuickFormRender{
	private $id;
	private $model = array();
	private $modelFactory;
	private $modelConnector;
	
	function QuickFormRender($id){
		$this->id = $id;
	}
	
	public function append($name, $modelColumn){
		$this->model[$name] = $modelColumn;
		$message = $modelColumn->check();
		if(strlen($message) and state_is_develop()){
			notify_add_error('Model corrupted : '.$name.' : '.$message);
		}
	}
	
	public function setModel($model){
		$this->modelFactory = new ModelFactory($this->id, $model);
		$this->modelConnector = $modelFactory->bind();
		$column = $this->modelConnector->getColumnName();
		$this->model = array();
		foreach($column as $key => $value){
			$this->model[$value] = $this->modelConnector->getColumn();
		}
	}
	
	public function reset(){
		$this->model = array();
	}
	
	public function render(){
		$modelConnector = new ModelConnector($this->model, null);
		$rednerArray = array(
			'id' => $this->id,
			'form' => form($this->id, $this->model),
			'label' => $modelConnector->getColumnAttribute('label'),
			'help' => $modelConnector->getColumnAttribute('help'),
			'not_null' => $modelConnector->getColumnNameByBoolean('isNotNull'),
		);
		return render($rednerArray, 'quickform.tpl', 'render_quick_form');
	}
}

?>
