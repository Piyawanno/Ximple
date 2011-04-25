<?php
require_once('ModelFactory.class.inc');

class QuickTableCreator{
	private $moduleName;
	private $modelFactory;
	private $modelConnector;
	private $tableCreator;
	
	function QuickTableCreator($moduleName, $model){
		$this->modelFactory = new ModelFactory($moduleName, $model);
		$this->modelConnector = $this->modelFactory->bind();
		$this->tableCreator = new TableCreator($this->modelConnector, $moduleName);
	}
	
	public function create(){
		$this->tableCreator->create();
	}
}

?>
