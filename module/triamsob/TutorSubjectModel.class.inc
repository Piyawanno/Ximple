<?php
class TutorSubjectModel extends Model{
	function TutorSubjectModel($ownerID){
		$this->owner = $this->hidden($ownerID, 'int');
		$this->subject = $this->checkbox(tt('subject'), triamsob_get_tutor_subjects());
	}
}
?>
