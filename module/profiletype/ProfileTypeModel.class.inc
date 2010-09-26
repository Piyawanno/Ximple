<?php
class ProfileTypeModel extends Model{
	function ProfileTypeModel(){
		$this->name = $this->title(tt('type name'));
		$this->description = $this->plain(tt('description'));
		$this->description->isList = true;
		$this->description->isReachable = true;
		$this->section = $this->section();
	}
}
?>
