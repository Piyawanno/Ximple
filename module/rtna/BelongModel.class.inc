<?php
require_once('rtna.tool.inc');

class BelongModel extends Model{
	function BelongModel(){
		$this->name = $this->title(tt('name'));		
		$this->is_leaf = $this->enable(tt('is base belong'));
		$this->parent = $this->select(tt('parent'), rtna_get_parent_option());
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->section = $this->section();
	}
}
?>