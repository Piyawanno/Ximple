<?php
class DocGenModel extends Model{
	function DocGenModel(){
		$this->place = $this->title(tt('place'));
		$this->place->isList = false;
		$this->document_id = $this->title(tt('document ID'));
		$this->document_id->isList = false;
		$this->write_date = $this->calendar(tt('write date'));
		
		$this->topic = $this->title(tt('topic'));
		$this->topic->type = 'shorttext';
		$this->topic->listMode = 'docgen';
		
		$prefixOption = array(
			0 => tt('prefix I'),
			1 => tt('prefix II'),
			2 => tt('prefix III'),
		);
		$this->prefix = $this->select(tt('prefix'), $prefixOption);
		$this->receiver = $this->char(tt('receiver'));
		$this->receiver->isReachable = true;
		
		$this->content = $this->plain(tt('content'));
		$this->content->isReachable = true;
		$this->writer_rank = $this->title(tt('rank of writer'));
		$this->writer_rank->isList = false;
		$this->writer_position = $this->title(tt('position of writer'));
		$this->writer_position->isList = false;
		$this->contributor = $this->owner();
		$this->contributor->label = tt('contributor');
		$this->section = $this->section();
	}
}
?>
