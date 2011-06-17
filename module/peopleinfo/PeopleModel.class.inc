<?php
require_once(MODULE_PATH.'freetag/FreeTagColumn.class.inc');
require_once('peopleinfo.tool.inc');
require('PeopleColumn.class.inc');

class PeopleModel extends Model{
	function PeopleModel(){
		$this->name = $this->title(tt('name'));
		$this->name->listMode = 'peopleinfo';
		$this->avatar = $this->image(tt('avatar'), 'files/avatar/', 180);
		$this->uid = new PeopleColumn();
		$this->status = $this->select(tt('status'), peopleinfo_get_people_status());
		$this->status->isList = true;
		$this->status->listMode = 'peopleinfo_status';
		
		$this->profile = $this->text(tt('generic information'));
		$this->profile->isReachable = true;
		
		$this->update_time = $this->now();
		$this->update_time->isUpdateTime = true;
		$this->update_time->formatDateBySelect = true;
		$this->update_time->dateFormat = cc('time_format').' H:i';
		
		$this->creator = $this->owner();
		
		$this->freetag = new FreeTagColumn('peopleinfo');
		$this->section = $this->section();
	}
	
	public function triggerPostDBInsert(){
		$this->setAvatar();
	}
	
	public function triggerPostDBUpdate(){
		$this->setAvatar();
	}
	
	public function triggerSelect($data){
		$this->people->option = peopleinfo_get_people_name();
		return $data;
	}
	
	private function setAvatar(){
		$data = array(
			'avatar' => $this->avatar->data,
		);
		db_update('users', $data, $this->uid->data);
	}
}
?>
