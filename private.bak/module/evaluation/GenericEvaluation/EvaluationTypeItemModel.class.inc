<?php
include_once('EvaluationTypeTopicColumn.class.inc');

class EvaluationTypeItemModel extends Model{
	function EvaluationTypeItemModel(){
		$this->name = $this->title(tt('item'));
		$this->type = new EvaluationTopicColumn();
	}
}
?>
