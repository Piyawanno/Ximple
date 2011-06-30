<?php
require('PollChoiseModel.class.inc');

class PollModel extends Model{
	function PollModel(){
		$this->name = $this->title(tt('name'));
		$this->description = $this->shortText(tt('description'));
		$this->owner = $this->owner();
		$this->create_date = $this->now();
		$this->end_date = $this->calendar(tt('end date'));
		$this->permission = $this->radio(tt('permission'), poll_permission_option());
		$this->mode = $this->hidden(gg('mode'), 'char');
		$this->mode_id = $this->hidden(gg('mode_id'), 'char');
		$this->choises = $this->grid(tt('choises'))->setModel(new PollChoiseModel());
	}
}
?>
