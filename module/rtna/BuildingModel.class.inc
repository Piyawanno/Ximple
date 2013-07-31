<?php

class BuildingModel extends Model{
	function BuildingModel(){
		$this->name = $this->title(tt('name'));
		$this->name->listMode = 'rtna_building';
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>