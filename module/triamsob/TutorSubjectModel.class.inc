<?php
class TutorSubjectModel extends Model{
	function TutorSubjectModel(){
		$this->owner = $this->owner();
		$this->subject = $this->checkbox(tt('subject'), triamsob_get_tutor_subjects());
	}
}
?>
