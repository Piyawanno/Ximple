<?php
class PageModel extends ContentModel{
	function PageModel($parent){
		ContentModel::ContentModel('page');
		$this->comment_permission = new PageStatusColumn(tt('comment permission'), 'comment_permission');
		$this->publishing_status = new PageStatusColumn(tt('status'), 'publishing_status');
		$this->publishing_status->isList = true;
		$this->publishing_status->isTriggerSelect = true;
		$this->parent = $this->hidden($parent, 'int');
		$this->icon = $this->imageLoader(tt('icon'), 'files/directory/', 240);
		$this->author_name = $this->char(tt('author name'), tt('If blank, your login-name will be shown.'));
		$this->introduction = $this->shortText(tt('introduction'));
		$this->extendAfter('topic', 'icon');
		$this->extendAfter('topic', 'author_name');
		$this->extendAfter('topic', 'introduction');
	}
}

class PageStatusColumn extends ModelColumn{
	private $status;
	public $configuration;
	public $isTriggerSelect = false;
	
	function PageStatusColumn($label, $status){
		$this->label = $label;
		$this->form = 'radio';
		$this->type = 'int';
		$this->selection = array();
		$this->status = $status;
	}
	
	public function triggerInsertForm(){
		$this->defaultData = $this->configuration[$this->status.'_default'];
		$this->initSelect();
	}
	
	public function triggerUpdateForm(){
		$this->initSelect();
	}
	
	public function triggerSelect(){
		if($this->isTriggerSelect){
			$functionName = 'content_get_'.$this->status;
			$option = $functionName();
			$this->data = $option[$this->data];
		}
	}
	
	private function initSelect(){
		$functionName = 'content_get_'.$this->status;
		$option = $functionName();
		if(!(authority_group('page_admin') or authority_group('page_editor'))){
			$enabled = $this->configuration[$this->status];
			foreach($enabled as $key){
				$this->selection[$key] = $option[$key];
			}
		}else{
			$this->selection = $option;
		}
	}
}
?>
