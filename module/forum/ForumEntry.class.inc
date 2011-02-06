<?php
if(execute_get_class('forum') == null)  execute_add_class('forum', 'ForumEntry');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include_once('forum.tool.inc');
include('ForumEntryModel.class.inc');

class ForumEntry extends Content{
	function ForumEntry(){
		$this->tableName = 'forum_entry';
		$this->moduleName = 'forum_entry';
		$this->moduleTitle = tt('Forum Entry');
		$this->init(new ForumEntryModel());
		$this->writeLabel = tt('Write new Forum Entry');
		document_set_path(tt('Forum'), 'forum');
		menu_activate('forum');
	}
	
	public function write(){
		$this->prepareForum();
		return Content::write();
	}
	
	public function insert(){
		Content::insert();
	}
	
	public function edit(){
		$this->prepareForum();
		return Content::edit();
	}
	
	public function listPage(){
		$this->prepareForum();
		head_add_css('list.css');
		$renderArray = array(
			'data' => $this->getListData(),
			'forum' => forum_get_info(gg('forum')),
			'pager' => $this->pager->render('forum_entry_list/forum/'.gg('forum')),
		);
		return render($renderArray, 'forumlist.tpl', 'forumlist');
	}
	
	private function prepareForum(){
		$forumID = gg('forum');
		if($forumID){
			$allowedForums = forum_get_allowed_id();
			if(!in_array($forumID, $allowedForums)){
				error_denied();
			}
			forum_set_path($forumID);
		}
	}
	
	private function getListData(){
		$featuredData = $this->getListDataFromDB(1);
		$regularData = $this->getListDataFromDB(0);
		$data = array();
		foreach($featuredData as $key => $value){
			$value['icon'] = 'stick';
			$data[] = $value;
		}
		$regularData = $this->checkNew($regularData);
		foreach($regularData as $key => $value){
			if(isset($value['comment_no'])){
				if($value['comment_no'] > 25) $value['icon'] = 'veryhot';
				elseif($value['comment_no'] > 15) $value['icon'] = 'hot';
			}elseif(!$this->isCommentable($value['comment_permission'])){
				$value['icon'] = 'lock';
			}elseif($value['is_new']){
				$value['icon'] = 'new';
			}else{
				$value['icon'] = 'default';
			}
			$data[] = $value;
		}
		
		return $data;
	}
	
	private function isCommentable($permission){
		if($permission == 0) return true;
		elseif($permission == 1 and !authority_is_guest()) return true;
		else return false;
	}
	
	private function checkNew($data){
		$count = count_get_array('forum_entry'.USER_ID, array_keys($data));
		foreach($count as $id => $number){
			$data[$id]['is_new'] = ($number == 0);
		}
		return $data;
	}
	
	private function getListDataFromDB($status){
		$forumID = (int) gg('forum');
		$column = array(
			'id',
			'topic',
			'write_time',
			'writer',
			'last_commentator',
			'comment_time',
			'comment_permission'
		);
		$pattern = "WHERE forum=%d AND publishing_status=%d ORDER by comment_time DESC";
		$this->selectPage($column, 20, sprintf($pattern, $forumID, 0));
		$this->getCommentNumber();
		return $this->data;
	}
}
?>
