<?php
class PeopleFileModel extends Model{
	function PeopleFileModel($informationID){
		$this->information = $this->hidden($informationID, 'int');
		$this->file = $this->file('file');
		$this->type = $this->hidden('', 'char');
	}
}
?>
