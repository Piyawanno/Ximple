<?php
execute_add_extended_class('rtna', 'club', 'club');
include('clubModel.class.inc');

class Club extends Control{
	function Club(){
		$this->moduleTitle = tt('Club');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'club';
		$this->tableName = 'rtna_club';
		$this->init(new ClubModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_club');
	}

	public function index(){
		$this->id = (int) gg('id'); //$_GET['id']
		if($this->id != 0) return $this->renderDetailPage();
		else return $this->listPage();
	}

	private function renderDetailPage(){
		$this->select($this->column, 'WHERE id='.$this->id);
		print_r($this->data);
		$this->selectByID($this->column);
		print_r($this->dataByID);
		document_set_path($this->dataByID['serie_number']);
		$renderArray = array(
			'data' => $this->dataByID,
		);
		return render($renderArray, 'rtna_club.tpl', 'rtna_club');
	}
}
?>
