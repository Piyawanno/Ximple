<?php
class SelectionMethod{
	private $chromosomeArray;
	
	function SelectionMethod(chromosomeArray){
		$this->chromosomeArray = $chromosomeArray;
	}
	
	public function inPairParetoDominance($competitiveObj){
		list($horizontal, $vertical) = $this->caculateCoordinate($competitiveObj);
		
		///
	}
	
	public function meetAllParetoDominance($competitiveObj){
		list($horizontal, $vertical) = $this->caculateCoordinate($competitiveObj);
		
		///
	}
	
	public function aggregationSum($competitiveObj){
		$objectiveResult = array();
		foreach($this->chromosomeArray as $key => $value){
			$objectiveResult[] = $competitiveObj->executeObjectiveFunctions($value);
		}
		
		///
	}
	
	public function priorityBase($competitiveObj){
		
		///
	}
	
	private function calculateCoordinate($competitiveObj){
		$horizontal = array();
		$vertical = array();
		foreach($this->chromosomeArray as $key => $value){
			$horizontal[] = $competitiveObj->horizontalOjectiveFunction($value);
			$vertical[]  = $competitiveObj->verticalOjectiveFunction($value);
		}
		return array($horizontal, $vertical);
	}
}
?>
