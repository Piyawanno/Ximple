<?php
require_once('EvaluationTypeColumn.class.inc');

class EvaluationModel extends Model{
	function EvaluationModel{
		$this->name = $this->title(tt('evaluation name'));
		$this->description = $this->shortText(tt('description'));
		$this->creator = $this->owner();
		$this->create_date = $this->now();
		$this->end_date = $this->calendar(tt('end date'));
		$this->type = new EvaluationTypeColumn();
		$this->status = $this->select(tt('status'), evaluation_status_option());
		$this->section = $this->section();
	}
}
?>
