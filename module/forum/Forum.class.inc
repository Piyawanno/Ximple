<?php
execute_add_class('forum', 'Forum');
include('ForumModel.class.inc');

class Forum extends Control{
	function Forum(){
		$this->moduleTitle = 'Forum';
		$this->moduleName = 'forum';
		$this->tableName = 'forum';
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'write');
		$this->addAccessMethod('guest', 'insert');
		$this->setAdmin('forum_admin');
		$this->init(new ForumModel());
	}
	
	public function initModule($requirement){
		Control::initModule($requirement);
		forum_set_panel();
	}
}
?>
