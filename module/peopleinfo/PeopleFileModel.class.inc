<?php
class PeopleFileModel extends Model{
	function PeopleFileModel($informationID){
		$this->information = $this->hidden($informationID, 'int');
		$this->description = $this->title(tt('short description'));
		$this->file = $this->file('file', 'files/peoipleinfo/');
		$this->type = $this->hidden('', 'char');
	}
}
?>
