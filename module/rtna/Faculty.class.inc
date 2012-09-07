<?php
execute_add_extended_class('rtna', 'faculty', 'Faculty');
include('FacultyModel.class.inc');

class Faculty extends Control{
	function Faculty(){
		$this->moduleTitle = tt('Faculty');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'faculty';
		$this->tableName = 'rtna_faculty';
		$this->init(new FacultyModel());
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_faculty');
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
		document_set_path($this->dataByID['faculty_name']);
		$renderArray = array(
			'data' => $this->dataByID,
		);
		return render($renderArray, 'rtna_faculty.tpl', 'rtna_faculty');
	}
}
?>