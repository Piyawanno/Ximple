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
		$this->faculty = $this->select(tt('faculty'), $option);

		$this->checkin_faculty = $this->spin(tt('checkin_faculty'));
		$this->description = $this->shortText(tt('description'));
	}
}
?>