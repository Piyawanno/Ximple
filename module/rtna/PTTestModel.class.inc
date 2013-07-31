<?php
require_once('rtna.tool.inc');

class PTTestModel extends Model{
	function PTTestModel(){
		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
		$this->test_date = $this->calendar(tt('test date'));
		$this->pushup = $this->spin(tt('push up [%]'), 0, 100);
		$this->situp = $this->spin(tt('sit up [%]'), 0, 100);
		$this->chinup = $this->spin(tt('chin up [%]'), 0, 100);
		$this->running = $this->spin(tt('running [%]'), 0, 100);
		$this->swimming = $this->spin(tt('swimming [%]'), 0, 100);
        $this->total = $this->hidden(0, 'int');
		$this->pass = $this->hidden(0, 'int');
		$this->section = $this->section();
	}

	public function triggerPostInsert(){
		$this->calculate();
	}
	
	public function triggerPostUpdate(){
		$this->calculate();
	}

	private function calculate(){
		$this->total->data = (pp('pushup') +  pp('situp') +  pp('chinup') +  pp('running') +  pp('swimming'))/5;
		$this->pass ->data = ($this->total->data > 60);
	}
} 
?>