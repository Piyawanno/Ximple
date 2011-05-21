<?php
class PeopleFileModel extends Model{
	function PeopleFileModel($informationID=null){
		$this->short_description = $this->title(tt('short description'));
		$this->file = $this->file('file', 'files/peoipleinfo/');
		$this->type = $this->hidden('', 'char');
		$this->type->isForm = false;
		$this->information = $this->hidden($informationID, 'int');
		$this->information->isForm = false;
	}
}
?>
