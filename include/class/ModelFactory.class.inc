<?php
class ModelFactory{
	private $model = array();
	private $modelObject;
	private $moduleName = '';
	
	function ModelFactory($moduleName, $modelObject){
		$this->moduleName = $moduleName;
		$this->modelObject = $modelObject;
	}
	
	public function bind(){
		foreach($this->modelObject as $key => $value){
			$beforeColumnName = $this->modelObject->getExtendedBefore($key);
			if(is_array($beforeColumnName)){
				foreach($beforeColumnName as $column){
					$this->model[$column] = $this->modelObject->$column;
				}
			}
			if(is_a($value, 'ModelColumn') and empty($this->model[$key])){
				$this->model[$key] = $value;
			}
			$afterColumnName = $this->modelObject->getExtendedAfter($key);
			if(is_array($afterColumnName)){
				foreach($afterColumnName as $column){
					$this->model[$column] = $this->modelObject->$column;
				}
			}
		}
		$this->check();
		return new ModelConnector($this->model, $this->modelObject);	
	}
	
	private function check(){
		foreach($this->model as $name => $col){
			$message = $col->check();
			if(strlen($message) and state_is_develop()){
				notify_add_error('Model corrupted : '.$name.' : '.$message);
			}
		}
	}
}
?>
