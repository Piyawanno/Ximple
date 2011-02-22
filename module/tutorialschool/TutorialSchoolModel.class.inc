<?php
class TutorialSchoolModel extends ContentModel{
	function TutorialSchoolModel(){
		ContentModel::ContentModel('tutorialschool');
		$this->checkPath();
		$this->icon = $this->imageLoader(tt('icon'), 'files/tutorialschool/');
		$this->intro = $this->text(tt('introduction'));
		$this->intro->enableTranslate();
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'intro');
	}
	
	private function checkPath(){
		$path  = ROOT_PATH.'files/tutorialschool/';
		if(!is_dir($path))  mkdir($path);
	}
}
?>
