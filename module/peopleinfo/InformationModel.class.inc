<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');

class InformationModel extends Model{
	function InformationModel(){
		$this->topic = $this->title(tt('topic'));
		$this->content = $this->text(tt('content'));
		$this->source_date = $this->calendar(tt('date'));
		$this->freetag = new FreeTagColumn();
		$this->freetag->isReachable = true;
	}
}
?>
