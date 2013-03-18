<?php
execute_add_extended_class('rtna', 'officer', 'Officer');
include('OfficerModel.class.inc');

class Officer extends Control{
	function Officer(){
		$this->moduleTitle = tt('Officer');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'officer';
		$this->tableName = 'rtna_officer';
		$this->init(new OfficerModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_officer_list');
	}

	public function index(){
		$this->id = (int) gg('id');
		if($this->id) return $this->renderPage();
		else return $this->renderList();
	}
	
	private function renderPage(){
		$this->selectByID($this->column);
		$this->data = userinfo_get_info($this->data, 'uid');
		$this->dataByID = $this->data[$this->id];
		document_set_path($this->dataByID['name'].' '.$this->dataByID['surname']);
		return render($this->dataByID, 'rtna_officer.tpl', 'rtna_officer');
	}
	
	private function renderList(){
		$clause = 'WHERE section='.SECTION;
		$this->selectListPage(20, $clause);
		foreach($this->data as $key => $value){
			$this->data[$key]['name'] = $value['name'].' '.$value['surname'];
		}
		$this->listPageColumn = array('name');
		return $this->renderDefaultListPage();
	}
	
	private function setAccess(){
		$this->setAdmin('rtna_admin');
		$this->addAccessMethod('rtna_officer_data_manager', 'index');
		$this->addAccessMethod('rtna_officer_data_manager', 'write');
		$this->addAccessMethod('rtna_officer_data_manager', 'insert');
		$this->addAccessMethod('rtna_officer_data_manager', 'edit');
		$this->addAccessMethod('rtna_officer_data_manager', 'update');
		$this->addAccessMethod('rtna_officer_data_manager', 'drop');
		
	}

	private function setAction(){
		$this->addAction('rtna_officer_class', 'renderClassList');
		$this->addAction('develcard_drop_resolver', 'dropResolver');
	}
}
?>
