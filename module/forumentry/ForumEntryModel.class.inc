<?php
class ForumEntryModel extends ContentModel{
	function ForumEntryModel(){
		ContentModel::ContentModel('forumentry');
		$this->forum = new ForumColumn();
		$this->extendAfter('topic', 'forum');
	}
}

class ForumColumn extends ModelColumn{
	function ForumColumn(){
		$forumID = gg('forum');
		if(!$forumID and MODE == 'forumentry_edit'){
			$this->setAsSelect();
		}else{
			$this->setAsHidden($forumID);
		}
	}
	
	private function setAsHidden($forumID){
		$this->type = 'int';
		$this->form = 'hidden';
		$this->defaultData = $forumID;
		$this->data = $forumID;
	}
	
	private function setAsSelect(){
		$this->type = 'int';
		$this->label = tt('forum');
		$this->form = 'select';
		$forumID = forum_get_allowed_id();
		if(count($forumID)){
			$clause = 'WHERE id='.join(' OR id=', $forumID);
			$this->option = db_select_single_column('forum', 'name', $clause);
		}
	}
}
?>
