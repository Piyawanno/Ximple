<?php
class TriamsobConfigModel extends Model{
	function TriamsobConfigModel(){
		for($i=2; $i<=20;$i++){
			$option[] = $i;
		}
		$this->triamsob_word_wrap = $this->select(tt('number of shown senteces in index page'), $option);
		$this->triamsob_tutor_per_page = $this->select(tt('number of shown Tutors per page'), $option);
		$this->triamsob_admission_number = $this->select(tt('number of shown admission news'), $option);
		$this->triamsob_scholar_number = $this->select(tt('number of shown scholar news'), $option);
		$this->triamsob_exercise_number = $this->select(tt('number of shown exercise news'), $option);
		$this->triamsob_exam_number = $this->select(tt('number of shown exam news'), $option);
		$this->triamsob_tutor_number = $this->select(tt('number of shown tutor articles'), $option);
		$this->triamsob_student_number = $this->select(tt('number of shown student articles'), $option);
		$this->triamsob_forum_number = $this->select(tt('number of shown forum'), $option);
		
		$this->triamsob_tutor_group = $this->group(tt('tutor group'));
		$this->triamsob_tutor_group->form = 'select';
		$this->triamsob_pretutor_group = $this->group(tt('pending tutor group'));
		$this->triamsob_pretutor_group->form = 'select';
		
		$this->triamsob_admission_category = $this->category('journal', 'admission category');
		$this->triamsob_scholar_category = $this->category('journal', 'scholar category');
		$this->triamsob_exercise_category = $this->category('journal', 'exercise category');
		$this->triamsob_exam_category = $this->category('journal', 'exam category');
		$this->triamsob_tutor_category = $this->category('journal', 'tutor article category');
		$this->triamsob_student_category = $this->category('journal', 'student article category');
		
		$this->triamsob_registration_text = $this->shortText(tt('text for Tutor Registration Page'));
		$this->triamsob_registration_reply = $this->shortText(tt('text for Tutor Registration Reply'));
		$this->triamsob_tutor_help_text = $this->shortText(tt('text for Tutor Help'));
		
		$this->triamsob_place_type = new ProfileTypeColumn(tt('place'));
		$this->triamsob_phone_type = new ProfileTypeColumn(tt('phone'));
		$this->triamsob_facebook_type = new ProfileTypeColumn(tt('facebook'));
		$this->triamsob_degree_type = new ProfileTypeColumn(tt('degree'));
		$this->triamsob_experince_type = new ProfileTypeColumn(tt('experince'));
		$this->triamsob_etc_type = new ProfileTypeColumn(tt('etc.'));
	}
}

class ProfileTypeColumn extends ModelColumn{
	function ProfileTypeColumn($label, $help=null){
		$this->type = 'int';
		$this->form = 'select';
		$this->label = $label;
		$this->help = $help;
		$this->getOption();
	}
	
	
	private function getOption(){
		$clause = 'WHERE section='.SECTION;
		$this->option = db_select_single_column('profiletype', 'name', $clause);
	}
}
?>
