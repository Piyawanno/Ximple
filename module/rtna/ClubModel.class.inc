<?php
require_once('rtna.club.inc');

class ClubModel extends Model{
	function ClubModel(){
		$this->name = $this->title(tt('name'));
		$this->rtna_regiment_officer = $this->select(tt('rtna_regisment_officer'), rtna_get_rtna_regiment_officer_option());
		$this->rtna_cadet = $this->select(tt('rtna_clubleader'), rtna_get_rtna_cadet_option());
	}
}
?>