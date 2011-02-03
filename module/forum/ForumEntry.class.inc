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
	
	public function edit(){
		$this->prepareForum();
		return Content::write();
	}
	
	public function listPage(){
		$forumID = (int) gg('forum');
		if(empty($forumID)) error_denied();
		$pageID = (int) gg('page');
		head_add_css('list.css');
		list($forumName, $forumDescription) = forum_set_path($forumID);
		
		$column = array('topic', 'write_time', 'writer', 'last_commentator', 'comment_time');
		$pattern = "WHERE forum=%d AND publishing_status='%s' ORDER by comment_time DESC";
		if(empty($pageID)){
			$this->selectPage($column, 20, sprintf($forumID, 'featured'));
			$featuredData = $this->data;
		}
		$this->selectPage($column, 20, sprintf($forumID, 'published'));
		$data = $this->data;
		$renderArray = array(
			'featured' => $featuredData,
			'data' => $data,
			'forum_name' => $forumName,
			'forum_description' => $forumDescription,
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
}
?>
