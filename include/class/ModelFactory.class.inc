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
			if($beforeColumnName){
				$this->model[$beforeColumnName] = $this->modelObject->$beforeColumnName;
			}
			if(is_a($value, 'ModelColumn') and empty($this->model[$key])){
				$this->model[$key] = $value;
			}
			$afterColumnName = $this->modelObject->getExtendedAfter($key);
			if($afterColumnName){
				$this->model[$afterColumnName] = $this->modelObject->$afterColumnName;
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
