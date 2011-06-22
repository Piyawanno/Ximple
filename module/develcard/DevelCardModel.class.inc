<?php
include_once(MODULE_PATH.'freetag/FreeTagColumn.class.inc');

class DevelCardModel extends Model{
	function DevelCardModel(){
		$this->topic = $this->title(tt('topic'));
		$this->topic->listMode = 'develcard_display';
		
		$this->owner = $this->owner();
		
		$this->create_date = $this->now();
		$this->create_date->label = tt('created');
		$this->create_date->isList = true;
		$this->create_date->isReachable = true;
		
		$type = cc('develcard_type');
		if(!is_array($type)) $type = develcard_get_default_type_option();
		$this->type = $this->select(tt('type'), $type);
		$this->type->isList = true;
		$this->type->isReachable = true;
		
		if(develcard_is_admin()) $this->initAdminColumns();
		else $this->initContributorColumns();
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isReachable = true;
		$this->freetag = new FreeTagColumn('peopleinfo_event');
		
		$this->section = $this->section();
	}
	
	private function initAdminColumns(){
		require_once('ResolverModel.class.inc');
		$this->priority = $this->select(tt('priority'), develcard_get_priority_option());
		$this->priority->isList = true;
		$this->priority->isReachable = true;
		
		$this->status = $this->select(tt('status'), develcard_get_status_option());
		$this->resolver = $this->grid(tt('resolvers'))->setModel(new ResolverModel());
		
		$this->deadline = $this->calendar(tt('deadline'));
		$this->deadline->isList = true;
	}
	
	private function initContributorColumns(){
		$this->priority = $this->hidden(2, 'int');
		$this->status->defaultData = 0;
		
		$this->deadline = $this->now();
		$this->deadline->defaultData = time() + 60*60*24*7;
	}
}
?>
