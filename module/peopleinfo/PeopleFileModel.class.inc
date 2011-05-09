<?php
class PeopleFileModel extends Model{
	function PeopleFileModel($informationID=null){
		$this->information = $this->hidden($informationID, 'int');
		$this->file = $this->file('file', 'files/peoipleinfo/');
		$this->type = $this->hidden('', 'char');
	}
}
?>
