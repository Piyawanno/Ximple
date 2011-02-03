<?php
class ForumEntryModel extends ContentModel{
	function ForumEntryModel(){
		ContentModel::ContentModel('forum_entry');
		$this->forum = new ForumColumn();
		$this->extendAfter('topic', 'forum');
		$this->last_commentator = $this->hidden('', 'char');
		$this->publish_time = $this->now();
		
		$this->category->form = 'hidden';
		$this->category->defaultData = 0;
		
		$this->freetag->form = 'hidden';
		$this->freetag->isReachable = false;
		$this->freetag->help = null;
		
		$this->uri->form = 'hidden';
		$this->uri->isReachable = false;
		$this->uri->help = null;
		
		$this->description->form = 'hidden';
		$this->description->isReachable = false;
		$this->description->help = null;
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
