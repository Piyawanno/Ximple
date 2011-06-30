<?php
class PollVoteModel extends Model{
	public $tableName = 'pole_vote';
	
	function PollVoteModel(){
		$this->choise = $this->none(null, 'int');
		$this->voter = $this->owner();
		$this->voter_ip = $this->none(null, 'char');
	}
}
?>
