<?php
require_once('rtna.tool.inc');

class CadetModel extends Model{
	function CadetModel(){
		$this->rank = $this->select(tt('rank'), rtna_get_cadet_rank_option());
		$this->name = $this->title(tt('name'));
		$this->surname = $this->title(tt('surname'));
		$this->birth_date = $this->calendar(tt('birth date'));
		$this->uid = $this->userByRole(tt('login user'), 'rtna_cadet');
		
		$uri = SECTION_URI.Q.'rtna_yearserie_write';
		$pattern = tt('You can add new Year Serie with <a href="%s">this page</a>.');
		$help = sprintf($pattern, $uri);
		$this->year_serie = $this->select(tt('year serie'), rtna_get_yearserie_option(), $help);
		
		$uri = SECTION_URI.Q.'rtna_faculty_write';
		$pattern = tt('You can add new Faculty with <a href="%s">this page</a>.');
		$help = sprintf($pattern, $uri);
		$this->faculty_name = $this->select(tt('faculty'), rtna_get_faculty_option(), $help);
		
		$this->party = $this->select(tt('party'), rtna_get_cadet_party_option());		
		$this->section = $this->section();
	}
}
?>
