<?php
class MeetingParicipantModel extends ContentModel{
	function MeetingParicipantModel(){
		$this->participant = $this->owner();
		$this->meeting = $this->hidden(null, 'int');
	}
}
?>
