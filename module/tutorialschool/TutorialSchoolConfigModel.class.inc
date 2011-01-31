<?php
class TutorialSchoolConfigModel extends ContentConfigModel{
	function TutorialSchoolConfigModel(){
		ContentConfigModel::ContentConfigModel('tutorialschool');
		
		$option = array(
			'avatar' => tt('show avatar'),
			'category_icon' => tt('show category icon'),
			'comment_avatar' => tt('show avatar for comments'),
			'signature' => tt('user signature'),
			'sibling' => tt('next/previous entry'),
		);
		$this->tutorialschool_appearance = $this->checkbox(tt('show in rendered tutorialschool'), $option);
		
		$option = array(3 => 3, 5 => 5, 8 => 8, 10 => 10, 15 => 15, 20 => 20);
		$this->tutorialschool_entries_number = $this->select(tt('tutorialschool entries per page'), $option);
		$this->extendBefore('tutorialschool_comment_write_label', 'tutorialschool_entries_number');
	}
}
?>
