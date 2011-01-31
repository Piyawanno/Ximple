<?php
class TutorRegistrationModel extends UserMOdel{
	function TutorRegistrationModel(){
		UserModel::UserModel();
		$option = triamsob_get_tutor_subjects();
		$this->subject = $this->checkbox(tt('subject'), $option);
		$this->extendAfter('avatar', 'subject');
	}
}
?>
