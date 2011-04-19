<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');
include_once('ContentStatusColumn.class.inc');

abstract class ContentModel extends Model{
	private $commentPermission; 
	private $publishingStatus;
	
	function ContentModel($moduleName){
		$this->commentPermission = content_get_comment_permission();
		
		$this->publishingStatus = content_get_publishing_status();
		
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = $moduleName;
		$this->topic->enableTranslate();
<<<<<<< HEAD
=======
		
>>>>>>> 50ec279340597ee852a53be710f1b90c2c45e8ee
		$this->writer = $this->owner();
		$this->writer->label = tt('writer');
		
		$this->write_time = $this->now();
		
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		
		$this->publish_time = $this->calendar(tt('publish date'));
<<<<<<< HEAD
		$this->comment_time = $this->hidden('0000-00-00', 'timestamp');
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		$this->content->enableTranslate();
		$this->comment_permission = new ContentStatusColumn(tt('comment permission'), 'comment_permission', $moduleName);
		$this->publishing_status = new ContentStatusColumn(tt('status'), 'publishing_status', $moduleName);
		$this->publishing_status->isList = true;
		$this->publishing_status->isTriggerSelect = true;
=======
		
		$this->comment_time = $this->hidden('0000-00-00', 'timestamp');
		
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		$this->content->enableTranslate();
		
		$commentPermission = new ContentStatusColumn(tt('comment permission'), $moduleName);
		$commentPermission->setStatus('comment_permission');
		$commentPermission->setOption($this->getCommentPermission());
		$this->comment_permission = $commentPermission;
		
		$publishingStatus = new ContentStatusColumn(tt('status'), $moduleName);
		$publishingStatus->setStatus('publishing_status');
		$publishingStatus->setOption($this->getPublishingStatus());
		$publishingStatus->isList = true;
		$publishingStatus->isTriggerSelect = true;
		$this->publishing_status = $publishingStatus;
		
>>>>>>> 50ec279340597ee852a53be710f1b90c2c45e8ee
		$help = tt('You can use "extended URI" to increase search engine optimozation. ');
		$help.= tt('This will appear in URI to this entry without any effect.');
		$this->uri = $this->char(tt('extended URI'), $help);
		$this->uri->isReachable = true;
<<<<<<< HEAD
		$help = tt('Short description about this content for search engine optimization. ');
		$this->description = $this->plain(tt('description'), $help);
		$this->description->isReachable = true;
=======
		
		$help = tt('Short description about this content for search engine optimization. ');
		$this->description = $this->plain(tt('description'), $help);
		$this->description->isReachable = true;
		
>>>>>>> 50ec279340597ee852a53be710f1b90c2c45e8ee
		$this->category = $this->category($moduleName);
		
		$this->freetag = new FreeTagColumn();
		$this->freetag->isReachable = true;
		
		$this->section = $this->section();
		
		if(uu('editor') == 1 or uu('editor') == 2){
			$this->code = $this->plain(tt('code writer'));
		}else{
			$this->code = $this->hidden('', 'shorttext');
		}
	}
	
	public function getCommentPermission(){
		return $this->commentPermission;
	}
	
	public function getPublishingStatus(){
		return $this->publishingStatus;
	}
}
?>
