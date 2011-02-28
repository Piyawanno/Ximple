<?php
class TriamsobConfigModel extends Model{
	function TriamsobConfigModel(){
		$this->triamsob_registration_text = $this->shortText(tt('Text for Tutor Registration'));
		$this->triamsob_tutor_help_text = $this->shortText(tt('Text for Tutor Help'));
	}
}
?>
