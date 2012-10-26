<?php
require_once('rtna.tool.inc');
class ClassroomModel extends Model{
	function ClassroomModel(){
		$this->name = $this->title(tt('name'));
		$this->class_building = $this->select(tt('building'), rtna_get_building_option());
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>