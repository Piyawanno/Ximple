<?php
class EvaluationTypeModel extends Model{
	function EvaluationTypeModel(){
		$this->name = $this->title(tt('evaluation type name'));
		$this->description = $this->shortText(tt('description'));
		$this->creator = $this->owner();
		$this->create_date = $this->now();
		$this->section = $this->section();
	}
}
?>
