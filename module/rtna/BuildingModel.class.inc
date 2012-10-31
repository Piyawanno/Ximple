<?php

class BuildingModel extends Model{
	function BuildingModel(){
		$this->name = $this->title(tt('name'));
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>