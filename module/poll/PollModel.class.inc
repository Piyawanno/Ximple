<?php
require('PollChoiseModel.class.inc');

class PollModel extends Model{
	function PollModel(){
		$this->name = $this->title(tt('name'));
		$this->description = $this->shortText(tt('description'));
		$this->choises = $this->grid(tt('choises'))->setModel(new PollChoiseModel());
		$this->owner = $this->owner();
		
		$this->create_date = $this->now();
		$this->create_date->formatDateBySelect = true;
		$this->create_date->dateFormat = cc('time_format');
		
		$this->end_date = $this->calendar(tt('end date'));
		$this->end_date->defaultData = date('Y-m-d H:i:s', time() + 60*60*24*7);
		
		$this->permission = $this->radio(tt('permission'), poll_permission_option());
		$this->mode = $this->hidden(gg('mode'), 'char');
		$this->mode_id = $this->hidden(gg('mode_id'), 'char');
		$this->section = $this->section();
	}
}
?>
