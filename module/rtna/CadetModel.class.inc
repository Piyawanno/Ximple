<?php
class CadetModel extends Model{
	function CadetModel(){
		$this->name = $this->title(tt('name'));
		$this->surname = $this->title(tt('surname'));

		$option = db_select_single_column('users', 'login_name');
		$this->uid = $this->select(tt('login user'), $option);

		$option = db_select_single_column('rtna_yearserie', 'serie_number');
		$this->year_serie = $this->select(tt('year serie'), $option);

		
		$option = array(
			0 => tt('undefined'),
			1 => tt('naval'),
			2 => tt('mechanical'),
			3 => tt('marine'),
		);
		$this->party = $this->select(tt('party'), $option);

		
		$this->birth_date = $this->calendar(tt('birth date'));
	}
}
?>