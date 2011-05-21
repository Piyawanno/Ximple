<?php
class RelatedDataModifier{
	private $modelConnector;
	private $tableName;
	
	function RelatedDataModifier($tableName, $modelConnector){
		$this->setModelConnector($tableName, $modelConnector);
	}
	
	public function insert(){
		
	}
	
	public function setModelConnector($tableName, $modelConnector){
		$this->modelConnector = $modelConnector;
		$this->tableName = $tableName;
	}
}
?>
