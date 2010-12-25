<?php
class ForumEntryModel extends ContentModel{
	function ForumEntryModel(){
		ContentModel::ContentModel('forumentry');
		$this->checkPath();
		$this->forum = new ForumColumn();
		$this->extendAfter('topic', 'forum');
	}
}

class ForumColumn extends ModelColumn{
	function ForumClumn(){
		$forumID = gg('forum');
		if($forumID and MODE != 'forumentry_edit'){
			$this->setAsHidden($forumID);
		}else{
			$this->setAsSelect();
		}
	}
	
	private function setAsHidden($forumID){
		$this->type = 'int';
		$this->form = 'hidden';
		$this->defaultData = $forumID;
		$this->data = $forumID;
	}
	
	private function setAsSelect(){
	
	}
}
?>
