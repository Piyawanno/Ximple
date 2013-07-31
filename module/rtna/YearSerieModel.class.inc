<?php
class YearSerieModel extends Model{
	function YearSerieModel(){
		$this->serie_number = $this->spin(tt('serie number'), 105);
		$this->serie_number->isList = true;
		$this->serie_number->listMode = 'rtna_yearserie';

		$this->checkin_year = $this->spin(tt('checkin year'), 2007);
		$this->description = $this->shortText(tt('description'));
		$this->section = $this->section();
	}
}
?>