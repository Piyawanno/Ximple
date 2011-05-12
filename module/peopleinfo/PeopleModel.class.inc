<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');
include_once('peopleinfo.tool.inc');

class PeopleModel extends Model{
	function PeopleModel(){
		$this->people = $this->hidden(NULL);
		$this->people->label = tt('user');
		$this->people->isList = true;
		$this->people->isUser = true;
		$this->people->isOrderable = false;
		$this->people->isReachable = true;
		$this->people->listMode = 'peopleinfo';
		
		$this->status = $this->select(tt('status'), peopleinfo_get_people_status());
		$this->status->isList = true;
		
		$this->profile = $this->text('generic information');
		$this->profile->isReachable = true;
		
		$this->freetag = new FreeTagColumn();
		$this->section = $this->section();
	}
	
	public function triggerInsertForm(){
		$this->people->form = 'select';
		$this->people->option = peopleinfo_get_unprocessed_user();
		head_add_js_var('peopleUserNumber', count($this->people->option));
	}
	
	public function triggerUpdateForm(){
		head_add_js_var('peopleUserNumber', 1);
	}
	
	public function triggerSelect(){
		$this->people->option = peopleinfo_get_people_name();
	}
}
?>
