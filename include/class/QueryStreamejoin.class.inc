<?php
class QueryStreamTest{
	
	private $operation;
	private $conjunction;
	private $isConjunction = false;
	
	public function startAnd(){
		if(!$this->isConjunction){//ture			
			$this->conjunction = new QueryConjunction("AND");
		}
		$this->isConjunction =  true;
		
		//$conjunction = new QueryConjunction("AND");
		//$this->conjunction = $conjunction;
		
		
	}
	public function endAnd(){
		$this->isConjunction = false;
	}
	public function startOr(){
		if(!$this->isConjunction){
			$this->conjunction = new QueryConjunction("OR");
		}
		$this->isConjunction = true;
	
	}
	public function endOr(){
		$this->isConjunction = false;
	}
	public function equal($columnName , $value){
		$operation = new QueryOperation($columnName, $value , "=");
		
		if($this->isConjunction){		
			$this->conjunction->appendOperation($operation);			
		}else{
			$this->operation=$operation;
		}		
	}
	public function join($object){		
		$this->conjunction->appendOperation($object);	
		
	}

	public function notEqual($columnName , $value){
		$operation = new QueryOperation($columnName, $value , "!=");
		$this->operation=$operation;
	}		
	
	public function execute(){
		if($this->isConjunction){
			return $this->conjunction->execute();//สั่ง execute ของ QueryConjunction
		}else{
			return $this->operation->execute();
		}
	}
	
}

class QueryOperation{
	private $columnName;
	private $value;
	private $operation;
	//private $columnString;
	
	public  function QueryOperation($columnName , $value , $operation){
	
		$this->columnName=$columnName;
		$this->value=$value;
		$this->operation=$operation;
	}
	
#	public  function QueryJoin($columnString){
#	
#		$this->columnString=$columnString;
#	}
#	
	public function execute(){
	
		return  $this->columnName.' '.$this->operation." '".$this->value."' ";
	}
	
}

class QueryConjunction{
	private $type;
	private $operation = array();

	public function QueryConjunction($type){
		$this->type=$type;	
	
	}
	
	public function appendOperation($operation){
	
		$this->operation[] = $operation;
	}
	
	public function execute(){	
		$operation = array();
		foreach($this->operation as $key => $value){
			$operation[] = $value->execute();
		}
		return '('.join(' '.$this->type.' ', $operation).')';
	}


}
//เรียกใช้
$query = new QueryStreamTest();
$query->startAnd();
$query->equal("name", "valueI");
$query->equal("surname", "value II");
$query->startOr();
$query->equal("name", "valueI");
$query->equal("surname", "value II");
$query->endOr();
$query->endAnd();
echo ($query->execute());
/*$query = new QueryStreamTest();
$query->startOr();
$query->equal("C", "c");
$query->equal("D", "d");
$query->endOr();
$newquery = new QueryStreamTest();
$newquery->startAnd();
$newquery->equal("A", "a");
$newquery->equal("B", "b");
$newquery->join($query); 
$newquery->endAnd();
echo ($newquery->execute());*/
?>
