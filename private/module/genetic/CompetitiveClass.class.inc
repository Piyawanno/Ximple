<?php

require_once('SelectionMethod.class.inc');

class CompeptitiveClass{
	private $round;
	
	function CompeptitiveClass(){
		$round = 0;
	}
	
	public function generatePopulation(){
		// return array of chromosomes;
	}
	
	public function hasNext(){
		if($round < 100){
			$round++;
			return true;
		}else{
			$round = 0;
			return false;
		}
	}
	
	public function screen($chromosome){
		// Constrains
		// return true or false
	}
	
	public function select($chromosomeArray){
		$selectionMethod = new SelectionMethod($chromosomeArray);
		return $selectionMethod->inPairParetoDominance($this);
	}
	
	public function horizontalOjectiveFunction($chromosome){
		// Calculate TD
		// return TD
	}
	
	public function verticalOjectiveFunction($chromosome){
		// Calculate EP
		// return EP 
	}
}
?>
