<?php
execute_add_extended_class('rtna', 'yearserie', 'YearSerie');
include('YearSerieModel.class.inc');

class YearSerie extends Control{
	function YearSerie(){
		$this->moduleTitle = tt('YearSerie');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'yearserie';
		$this->tableName = 'rtna_yearserie';
		$this->init(new YearSerieModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_yearserie');
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
		return render($renderArray, 'rtna_yearserie.tpl', 'rtna_yearserie');
	}
}
?>
