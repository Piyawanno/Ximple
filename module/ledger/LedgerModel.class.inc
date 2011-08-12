<?php
class LedgerModel extends Model {
	function LedgerModel(){

		$account_chart_type = array(1=>1,2=>2,3=>3,4=>4,5=>5);

		$this->name		= $this->title(tt('name'));

		$this->parent		= $this->title(tt('parent'));
		$this->parent->setType('int');

		$this->account_type	= $this->select( tt('AccountType') , $account_chart_type );
		$this->account_type->setType('int');

		$this->has_child	= $this->select( tt('has_child'), array(0=>'Control',1=>'Sub'));
		$this->has_child->setType('int');

		$this->description	= $this->shortText(tt('description'));
		$this->section		= $this->section();
	}
}
?>
