<?php
include_once(MODULE_PATH.'freetag/FreeTagColumn.class.inc');

class DevelCardModel extends Model{
	function DevelCardModel(){
		if(develcard_is_admin()) $this->initAdminColumns();
		else $this->initContributorColumns();
		$this->reporter = $this->owner();
		$this->topic = $this->title(tt('topic'));

		$this->create_date = $this->now();
		$this->create_date->label = tt('created');
		$this->create_date->dateFormat = cc('time_format');
		$this->create_date->formatDateBySelect = true;
		
		$this->end_date = $this->now();
		$this->end_date->defaultData = time() + 60*60*24*7;
		
		$type = cc('develcard_type');
		if(!is_array($type)) $type = develcard_get_default_type_option();
		$this->type = $this->select(tt('type'), $type);
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isReachable = true;
		$this->freetag = new FreeTagColumn('peopleinfo_event');
		
		$this->section = $this->section();
	}
	
	private function initAdminColumns(){
		require_once('ResolverModel.class.inc');
		$this->reporter_name = $this->hidden(USER_NAME, 'char');
		$this->priority = $this->select(tt('priority'), develcard_get_priority_option());
		$this->priority->isReachable = true;
		
		$this->status = $this->select(tt('status'), develcard_get_status_option());
		$this->resolver = $this->grid(tt('resolvers'))->setModel(new ResolverModel());
		
		$this->deadline = $this->calendar(tt('deadline'));
	}
	
	private function initContributorColumns(){
		$this->reporter_name = $this->title(tt('your name'));
		$this->priority = $this->hidden(2, 'int');
		$this->status->defaultData = 0;
		
		$this->deadline = $this->now();
		$this->deadline->defaultData = time() + 60*60*24*7;
	}
}
?>
