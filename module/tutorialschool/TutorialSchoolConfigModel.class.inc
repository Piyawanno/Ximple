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
		
		$option = array(
			5 => 5,
			10 => 10,
			15 => 15,
			20 => 20,
			30 => 30,
			40 => 40,
			50 => 50,
			60 => 60,
			70 => 70,
			80 => 80,
			90 => 90,
			100 => 100,
			110 => 110,
			120 => 120,
		);
		$this->tutorialschool_entries_number = $this->select(tt('tutorialschool entries per page'), $option);
		$this->extendBefore('tutorialschool_comment_write_label', 'tutorialschool_entries_number');
	}
}
?>
