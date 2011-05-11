<?php
include_once(ROOT_PATH.'module/freetag/FreeTagColumn.class.inc');
include_once('peopleinfo.tool.inc');

class PeopleModel extends Model{
	function PeopleModel(){
		$option = peopleinfo_get_unprocessed_user();
		head_add_js_var('peopleUserNumber', count($option));
		$this->people = $this->select(tt('user'), $option);
		$this->status = $this->select(tt('status'), peopleinfo_get_people_status());
		$this->profile = $this->text('generic information');
		$this->profile->isReachable = true;
		$this->freetag = new FreeTagColumn();
		$this->section = $this->section();
	}
}
?>
