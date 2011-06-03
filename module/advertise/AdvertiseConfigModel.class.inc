<?php
class AdvertiseConfigModel extends Model{
	function AdvertiseConfigModel(){
		$this->position = $this->grid(tt('Advertise Position'));
		$position = Model::char(tt('position'));
		$position->data = cc('advertise_block_position');
		$this->position->append('advertise_block_position', $position);
	}
}
?>
