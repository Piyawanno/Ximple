<?php
class CadetModel extends Model{
	function CadetModel(){
		$this->name = $this->title(tt('name'));
		$this->surname = $this->title(tt('surname'));
		$this->birth_date = $this->calendar(tt('birth date'));

	}
}
?>