<?php
require_once('rtna.tool.inc');
require_once('CadetBedroomModel.class.inc');
class BedroomModel extends Model{
	function BedroomModel(){
		$this->bedroom = $this->title(tt('room'));
		$this->class_building = $this->select(tt('building'), rtna_get_building_option());
		$this->responsible_man = $this->select(tt('responsible man'), rtna_get_unit_option());
		$this->responsible_man->isList = true;
		$this->cadet_room = $this->grid(tt('cadet'))->setModel(new CadetBedroomModel());
		$this->section = $this->section();
		
	}

}
?>