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
		$this->addAccessMethod('guest', 'index');
		$this->addAction('forum_manage', 'manage');
		$this->addAction('forum_save_sort', 'saveSort');
		$this->insertRedirection = 'forum_manage';
		$this->updateRedirection = 'forum_manage';
		$this->init(new ForumModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		$clause = "WHERE mode='forum' AND section=".SECTION;
		$category = db_select('category', array('id', 'pic', 'category', 'description'), $clause);
		$renderArray = array(
			'data' => $this->getSortedData(),
			'category' => $category,
		);
		head_add_css('forum.css');
		head_add_css('list.css');
		head_add_css('form.css');
		return render($renderArray, 'forum.tpl', 'forum');
	}
	
	public function manage(){
		document_set_path(tt('Manage Forum'));
		$clause = "WHERE mode='forum' AND section=".SECTION;
		$category = db_select_single_column('category', 'category', $clause);
		$category[0] = tt('Disable');
		$renderArray = array(
			'data' => $this->getSortedData(),
			'category' => $category,
		);
		head_add_css('forum.css');
		head_add_css('list.css');
		head_add_css('form.css');
		return render($renderArray, 'forumedit.tpl', 'forumedit');
	}
	
	public function drop(){
		execute_set_db();
		document_set_redirect('forum_manage');
		$pattern = tt('Forum is not allowed to be dropped. You can use <a href="%s">manage page</a> to disable Forum.');
		$message = sprintf($pattern, SECTION_URI.Q.'forum_manage');
		notify_add_error($message);
	}
	
	public function listPage(){
		return $this->manage();
	}
	
	public function saveSort(){
		execute_set_db();
		document_set_redirect('forum_manage');
		$forumID = pp('forum');
		$category = pp('category');
		foreach($forumID as $key => $value){
			$data = array(
				'position' => $key,
				'category' => $category[$key],
			);
			db_update('forum', $data, $value);
		}
	}
	
	public function initModule($requirement){
		Control::initModule($requirement);
		forum_set_panel();
	}
	
	private function getSortedData(){
		$clause = "WHERE section=".SECTION.' ORDER BY position';
		$this->select($this->column, $clause);
		$data = array();
		foreach($this->data as $key => $value){
			if(isset($value['category']['id'])){
				$data[$value['category']['id']][] = $value;
			}else{
				$data[0][] = $value;
			}
		}
		return $data;
	}
}
?>
