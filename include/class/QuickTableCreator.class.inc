<?php
class QuickTableCreator{
	private $moduleName;
	private $modelFactory;
	private $modelConnector;
	private $tableCreator;
	
	function QuickTableCreator($moduleName, $model){
		$this->modelFactory = new ModelFactory($moduleName, $model);
		$this->modelConnector = $modelFactory->bind();
		$this->tableCreator = new TableCreator($modelConnector, $moduleName);
	}
	
	public function create(){
		$this->tableCreator->create();
	}
}

?>
