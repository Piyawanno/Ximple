<?php
require_once('rtna.tool.inc');

class ClubModel extends Model{
	function ClubModel(){
		$this->name = $this->title(tt('name'));
		$this->rtna_officer = $this->select(tt('staff officer'), rtna_get_rtna_officer_option());
		$this->rtna_cadet = $this->select(tt('rtna clubleader'), rtna_get_rtna_cadet_option());
		$this->section = $this->section();
	}
}
?>