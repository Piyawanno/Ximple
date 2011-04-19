<?php
<<<<<<< HEAD
class ForumEntryModel extends Model{
	function ForumEntryModel(){
		$this->commentPermission = content_get_comment_permission();
		$this->publishingStatus = content_get_publishing_status();
		
		$moduleName = 'forum_entry';
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = $moduleName;
		$this->forum = new ForumColumn();
		
		$this->writer = $this->owner();
		$this->writer->label = tt('writer');
		
		if(authority_is_guest()){
			$this->writer_name = $this->title(tt('your name'));
		}else{
			$this->writer_name = $this->hidden(USER_NAME, 'char');
			$this->writer_name->label = tt('writer');
			$this->writer_name->isList = true;
		}
		
		$this->write_time = $this->now();
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		$this->comment_time = $this->now();
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		$this->section = $this->section();
		$this->last_commentator = $this->hidden('', 'char');
		$this->last_commentator_id = $this->owner();
		
		if(!authority_is_guest()){
			$this->comment_permission = new ContentStatusColumn(tt('comment permission'), 'comment_permission', $moduleName);
			$this->publishing_status = new ContentStatusColumn(tt('status'), 'publishing_status', $moduleName);
			$this->publishing_status->isList = true;
			$this->publishing_status->isTriggerSelect = true;
		}else{
			$this->comment_permission = $this->hidden(cc('forum_comment_permission_default'), 'int');
			$this->publishing_status = $this->hidden(cc('forum_publishing_status_default'), 'int');
		}
	}
}

class ForumColumn extends ModelColumn{
	private $isSelect;
	
	function ForumColumn(){
		$forumID = gg('forum');
		if(!$forumID) $this->setAsSelect();
		else $this->setAsHidden($forumID);
	}
	
	public function triggerInsertForm(){
		if($this->isSelect) $this->getOption();
	}
	
	public function triggerUpdateForm(){
		if($this->isSelect) $this->getOption();
	}
	
	private function setAsHidden($forumID){
		$this->type = 'int';
		$this->form = 'hidden';
		$this->defaultData = $forumID;
		$this->data = $forumID;
		$this->isSelect = false;
	}
	
	private function setAsSelect(){
		$this->type = 'int';
		$this->label = tt('forum');
		$this->form = 'select';
		$this->option = array();
		$this->isSelect = true;
	}
	
	private function getOption(){
		$forumID = forum_get_writable_id();
		if(count($forumID)){
			$clause = 'WHERE id='.join(' OR id=', $forumID);
			$this->option = db_select_single_column('forum', 'name', $clause);
		}elseif(forum_check_authority_group()){
			$this->option = array();
			$pattern = tt('No Forum is created, please <a href="%s">create forum</a> before write a new entry.');
			$message = sprintf($pattern, SECTION_URI.Q.'forum_manage');
			notify_add_error($message);
=======
include('ForumColumn.class.inc');

class ForumEntryModel extends Model{
	private $commentPermission;
	private $publishingStatus;
	
	function ForumEntryModel(){
		$this->commentPermission = content_get_comment_permission();
		$this->publishingStatus = forum_get_publishing_status();
		
		$moduleName = 'forum_entry';
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = $moduleName;
		$this->forum = new ForumColumn();
		
		$this->writer = $this->owner();
		$this->writer->label = tt('writer');
		
		if(authority_is_guest()){
			$this->writer_name = $this->title(tt('your name'));
		}else{
			$this->writer_name = $this->hidden(USER_NAME, 'char');
			$this->writer_name->label = tt('writer');
			$this->writer_name->isList = true;
		}
		
		$this->write_time = $this->now();
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		$this->comment_time = $this->now();
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		$this->section = $this->section();
		$this->last_commentator = $this->hidden('', 'char');
		$this->last_commentator_id = $this->owner();
		
		if(!authority_is_guest()){
			$commentPermission = new ContentStatusColumn(tt('comment permission'), $moduleName);
			$commentPermission->setStatus('comment_permission');
			$commentPermission->setOption($this->commentPermission);
			$this->comment_permission = $commentPermission;
	
			$publishingStatus = new ContentStatusColumn(tt('status'), $moduleName);
			$publishingStatus->setStatus('publishing_status');
			$publishingStatus->setOption($this->publishingStatus);
			$publishingStatus->isList = true;
			$publishingStatus->isTriggerSelect = true;
			$this->publishing_status = $publishingStatus;
>>>>>>> 50ec279340597ee852a53be710f1b90c2c45e8ee
		}else{
			$this->comment_permission = $this->hidden(cc('forum_comment_permission_default'), 'int');
			$this->publishing_status = $this->hidden(cc('forum_publishing_status_default'), 'int');
		}
	}
}
?>
