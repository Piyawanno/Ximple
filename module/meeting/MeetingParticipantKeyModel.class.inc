<?php
class MeetingParicipantKeyModel extends ContentModel{
	function MeetingParicipantKeyModel(){
		$this->participant = $this->owner();
		$this->meeting = $this->hidden(null, 'int');
		$this->key = $this->hidden(null, 'char');
	}
}
?>
