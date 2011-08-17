<?php
require_once('GeneticOperator.class.inc');

class Population{
	private $chromosomeArray;
	private $competitiveObject = null;
	
	function Population($competitiveObject){
		$this->competitiveObject = $competitiveObject;
		$this->chromosomeArray = $competitiveObject->generatePopulation();
	}
	
	public function getPopulation(){
		while($this->competitiveObject->hasNext()){
			$this->produceChromosome();
			$this->screen();
			$this->selectChromosome();
		}
		return $this->chromosomeArray;
	}
	
	private function produceChromosome(){
		$this->produceCrossOver();
		$this->produceMutation();
	}
	
	private function selectChromosome(){
		$this->chromosomeArray = $this->competitiveObject->select($this->chromosomeArray);
	}
	
	private function produceCrossOver(){
		$chromosomeLength = count($this->chromosomeArray));
		for($i=0; $i < $chromosomeLength-1;$i++){
			$father = $this->chromosomeArray[$i];
			$mother = $this->chromosomeArray[$i+1];
			$children = GeneticOperator::crossOver($father, $mother);
			$this->chromosomeArray = array_merge($this->chromosomeArray, $children);
		}
	}
	
	private function produceMutation(){
		$mutated = array();
		foreach($this->chromosomeArray as $key => $value){
			$mutated[] = GeneticOperator::mutate($value);
		}
		$this->chromosomeArray = array_merge($this->chromosomeArray, $mutated);
	}
	
	private function screen(){
		$screened = array();
		foreach($this->chromosomeArray as $key => $value){
			if($this->competitiveObject->screen($value)){
				$screened[] = $value;
			}
		}
		$this->chromosomeArray = $screened; 
	}
}
?>
