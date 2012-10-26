<?php
require_once('rtna.tool.inc');

class CadetModel extends Model{
	function CadetModel(){
		$this->rank = $this->select(tt('rank'), rtna_get_cadet_rank_option());
		$this->name = $this->title(tt('name'));
		$this->surname = $this->title(tt('surname'));
		$this->birth_date = $this->calendar(tt('birth date'));
		$this->uid = $this->select(tt('login user'), rtna_get_cadet_uid_option());
		
		$uri = SECTION_URI.Q.'rtna_yearserie_write';
		$pattern = tt('You can add new Year Serie with <a href="%s">this page</a>.');
		$help = sprintf($pattern, $uri);
		$this->year_serie = $this->select(tt('year serie'), rtna_get_yearserie_option(), $help);
		
		$this->faculty_name = $this->select(tt('faculty'), rtna_get_faculty_option());
		$this->party = $this->select(tt('party'), rtna_get_cadet_party_option());
		$this->club = $this->select(tt('club'), rtna_get_club_option());
		$this->section = $this->section();
	}
}
?>
