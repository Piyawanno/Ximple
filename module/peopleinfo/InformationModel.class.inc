<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');

class InformationModel extends Model{
	function InformationModel(){
		$this->topic = $this->title(tt('topic'));
		$this->topic->isList = true;
		$this->topic->isReachable = true;
		
		$this->source_date = $this->calendar(tt('date'));
		$this->update_time = $this->now();
		
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		
		$this->freetag = new FreeTagColumn();
		$this->section = $this->section();
	}
}
?>
