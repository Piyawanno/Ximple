<?php

require_once(ROOT_PATH.'include/tool/form.tool.inc');

class QuickFormRender{
	private $id;
	private $model = array();
	
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
