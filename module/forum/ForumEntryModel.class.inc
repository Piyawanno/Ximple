<?php
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
			$this->writer_name= $this->title(tt('your name'));
		}else{
			$this->writer_name= $this->hidden(USER_NAME, 'char');
		}
		$this->write_time = $this->now();
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		$this->comment_time = $this->hidden('0000-00-00', 'timestamp');
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		$this->comment_permission = new ContentStatusColumn(tt('comment permission'), 'comment_permission', $moduleName);
		$this->publishing_status = new ContentStatusColumn(tt('status'), 'publishing_status', $moduleName);
		$this->publishing_status->isList = true;
		$this->publishing_status->isTriggerSelect = true;
		$this->section = $this->section();
		$this->last_commentator = $this->hidden('', 'char');
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
		$forumID = forum_get_allowed_id();
		if(count($forumID)){
			$clause = 'WHERE id='.join(' OR id=', $forumID);
			$this->option = db_select_single_column('forum', 'name', $clause);
		}elseif(authority_group('forum_admin')){
			$this->option = array();
			$pattern = tt('No Forum is created, please <a href="%s">create forum</a> before write a new entry.');
			$message = sprintf($pattern, SECTION_URI.Q.'forum_manage');
			notify_add_error($message);
		}else{
			$this->option = array();
			error_denied();
		}
	}
}
?>
