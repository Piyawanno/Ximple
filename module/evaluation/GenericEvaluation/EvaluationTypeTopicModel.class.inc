<?php
class EvaluationTypeTopicModel extends Model{
	function EvaluationTypeTopicModel(){
		$this->name = $this->title(tt('topic'));
		$this->type = new EvaluationTypeColumn();
	}
}
?>
