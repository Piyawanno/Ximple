<?php
execute_add_class('forum', 'Forum');
include('ForumModel.class.inc');
include_once('forum.tool.inc');

class Forum extends Control{
	function Forum(){
		$this->moduleTitle = 'Forum';
		$this->moduleName = 'forum';
		$this->tableName = 'forum';
		$this->setAdmin('forum_admin');
		$this->setAccess();
		$this->setAction();
		$this->init(new ForumModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function manage(){
		document_set_path(tt('Manage Forum'));
		$clause = "WHERE mode='forum' AND section=".SECTION;
		$category = db_select_single_column('category', 'category', $clause);
		$clause = "WHERE section=".SECTION;
		$this->select($this->column, $clause);
	}
	
	public function initModule($requirement){
		Control::initModule($requirement);
		forum_set_panel();
	}
	
	private function setAccess(){
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'write');
		$this->addAccessMethod('guest', 'insert');
	}
	
	private function setAction(){
		$this->addAction('forum_manage', 'manage');
	}
}
?>
