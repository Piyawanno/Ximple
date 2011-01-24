<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');

class ContentModel extends Model{
	private $commentPermission; 
	private $publishingStatus;
	
	function ContentModel($moduleName){
		$this->commentPermission = content_get_comment_permission();
		$this->publishingStatus = content_get_publishing_status();
		
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = $moduleName;
		$this->topic->enableTranslate();
		$this->writer = $this->owner();
		$this->writer->label = tt('writer');
		$this->write_time = $this->now();
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		$this->publish_time = $this->calendar(tt('publish date'));
		$this->comment_time = $this->hidden('00-00-00', 'char');
		$this->content = $this->text(tt('content'));
		$this->content->isReachable = true;
		$this->content->enableTranslate();
		$this->comment_permission = new ContentStatusColumn(tt('comment permission'), 'comment_permission', $moduleName);
		$this->publishing_status = new ContentStatusColumn(tt('status'), 'publishing_status', $moduleName);
		$this->publishing_status->isList = true;
		$this->publishing_status->isTriggerSelect = true;
		$this->description = $this->plain(tt('description'));
		$this->description->isReachable = true;
		$this->uri = $this->char(tt('URI'));
		$this->uri->isReachable = true;
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

class ContentStatusColumn extends ModelColumn{
	private $moduleName;
	private $status;
	
	public $isTriggerSelect = false;
	
	function ContentStatusColumn($label, $status, $moduleName){
		$this->label = $label;
		$this->form = 'radio';
		$this->type = 'int';
		$this->moduleName = $moduleName;
		$this->status = $status;
		$this->defaultData = cc($moduleName.'_'.$this->status.'_default');
		$functionName = 'content_get_'.$this->status;
		$this->option = $functionName();
	}
	
	public function triggerInsertForm(){
		$this->initSelect();
	}
	
	public function triggerUpdateForm(){
		$this->initSelect();
	}
	
	public function triggerSelect(){
		if($this->isTriggerSelect) $this->data = $this->option[$this->data];
	}
	
	private function initSelect(){
		$adminGroup = $this->moduleName.'_admin';
		$editorGroup = $this->moduleName.'_editor';
		if(!(authority_group($adminGroup) or authority_group($editorGroup))){
			$config = cc($this->moduleName.'_'.$this->status);
			$option = array();
			foreach($config as $key){
				$option[$key] = $this->option[$key];
			}
			$this->option = $option;
		}
	}
}
?>
