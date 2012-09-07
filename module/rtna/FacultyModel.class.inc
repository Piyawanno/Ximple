<?php
class FacultyModel extends Model{
	function FacultyModel(){
		$this->name = $this->title(tt('faculty name'));
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>