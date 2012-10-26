<?php
require_once('rtna.tool.inc');
require_once('ClubMemberModel.class.inc');
class ClasslogModel extends Model{
	function ClasslogModel(){
		$this->lecture_class = $this->title(tt('name'));
		$this->class_time = $this->timestamp(tt('class time'));
		$this->class_log = $this->shortText(tt('class log'));
		$this->description->isList = true;
		$this->cadet = $this->grid(tt('cadet'))->setModel(new ClubMemberModel());
		$this->section = $this->section();
	}
}
?>