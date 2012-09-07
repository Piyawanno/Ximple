<?php
class FacultyModel extends Model{
	function FacultyModel(){
		$option = array(
			0 => tt('Undefined'),
			1 => tt('Electrical Engineering'),
			2 => tt('Marine Engineering'),
			3 => tt('Hydrographic Engineering'),
			4 => tt('Management Science'),
			5 => tt('Naval Science'),
		);
		$this->faculty_select = $this->select(tt('faculty select'), $option);
		$this->faculty_select->isList = true;
		$this->faculty_select->listMode = 'rtna_faculty';

		$this->faculty_name = $this->spin(tt('faculty name'));
		$this->description = $this->shortText(tt('description'));
		$this->section = $this->section();
	}
}
?>