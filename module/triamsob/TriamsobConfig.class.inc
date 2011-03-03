<?php
execute_add_class('triamsob', 'TriamsobConfig');
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include('TriamsobConfigModel.class.inc');

class TriamsobConfig extends ConfigControl{
	function TriamsobConfig(){
		$this->moduleName = 'triamsob_config';
		$this->moduleTitle = tt('Triamsob Configuration');
		$this->setAdmin('triamsob_admin');
		$this->init(new TriamsobConfigModel());
	}
	
	public function index(){
		$appearance = $this->getNewConfigForm(tt('appearance'));
		$appearance->append('triamsob_word_wrap');
		$appearance->append('triamsob_tutor_per_page');
		$appearance->append('triamsob_admission_number');
		$appearance->append('triamsob_scholar_number');
		$appearance->append('triamsob_exercise_number');
		$appearance->append('triamsob_exam_number');
		$appearance->append('triamsob_tutor_number');
		$appearance->append('triamsob_student_number');
		$appearance->append('triamsob_forum_number');
		
		$group = $this->getNewConfigForm(tt('tutor group'));
		$group->append('triamsob_tutor_group');
		$group->append('triamsob_pretutor_group');
		
		$category = $this->getNewConfigForm(tt('category'));
		$category->append('triamsob_admission_category');
		$category->append('triamsob_scholar_category');
		$category->append('triamsob_exercise_category');
		$category->append('triamsob_exam_category');
		$category->append('triamsob_tutor_category');
		$category->append('triamsob_student_category');
		
		$profileType = $this->getNewConfigForm(tt('profile type for tutor'));
		$profileType->append('triamsob_place_type');
		$profileType->append('triamsob_phone_type');
		$profileType->append('triamsob_facebook_type');
		$profileType->append('triamsob_experince_type');
		$profileType->append('triamsob_degree_type');
		$profileType->append('triamsob_etc_type');
		
		document_set_path(tt('Triamsob'), 'triamsob');
		$this->formMeta->mode = 'triamsob_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
