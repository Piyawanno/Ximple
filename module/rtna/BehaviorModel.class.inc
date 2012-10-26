<?php
require_once('rtna.tool.inc');

class BehaviorModel extends Model{
	function BehaviorModel(){
		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
		$this->offense = $this->shortText(tt('offense'));
		$this->offense->isList = true;
		$this->point = $this->spin(tt('point'), 0, 200);
		$this->ondate = $this->calendar(tt('date'));
	}
}
?>