<?php
class EvaluationConfigModel extends Model{
	function EvaluationConfigModel(){
		$this->evaluation_index_page = $this->text(tt('welcome page'));
	}
}
?>
