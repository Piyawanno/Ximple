<?php
require_once('rtna.tool.inc');

class OfficerModel extends Model{
	function OfficerModel(){
		$this->rank = $this->select(tt('rank'), rtna_get_officer_rank_option());
		
		$this->name = $this->title(tt('name'));
		$this->name->listMode = 'rtna_officer';
		$this->surname = $this->title(tt('surname'));
		$this->birth_date = $this->calendar(tt('birth date'));
		$this->uid = $this->userByRole(tt('login user'), 'rtna_officer');

		$uri = SECTION_URI.Q.'rtna_yearserie_write';
		$pattern = tt('You can add new Year Serie with <a href="%s">this page</a>.');
		$help = sprintf($pattern, $uri);
				
		$this->party = $this->select(tt('party'), rtna_get_cadet_party_option());

		$uri = SECTION_URI.Q.'rtna_club_write';
		$pattern = tt('You can add new Clube with <a href="%s">this page</a>.');
		$help = sprintf($pattern, $uri);
		$this->club = $this->select(tt('club'), rtna_get_club_option(), $help);

		$this->section = $this->section();
	}
}
?>