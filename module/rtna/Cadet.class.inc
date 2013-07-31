<?php
execute_add_extended_class('rtna', 'cadet', 'Cadet');
include('CadetModel.class.inc');

class Cadet extends Control{
	function Cadet(){
		$this->moduleTitle = tt('Cadet');
		$this->moduleName = 'rtna';
		$this->moduleExtension = 'cadet';
		$this->tableName = 'rtna_cadet';
		$this->init(new CadetModel());
		
		$this->setAccess();
		$this->setAction();
		
		document_set_path(tt('RTNA Database'), 'rtna');
		document_set_path($this->moduleTitle, 'rtna_cadet_list');
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
		return render($this->dataByID, 'rtna_cadet.tpl', 'rtna_cadet');
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
		$this->addAccessMethod('rtna_cadet_data_manager', 'index');
		$this->addAccessMethod('rtna_cadet_data_manager', 'write');
		$this->addAccessMethod('rtna_cadet_data_manager', 'insert');
		$this->addAccessMethod('rtna_cadet_data_manager', 'edit');
		$this->addAccessMethod('rtna_cadet_data_manager', 'update');
		$this->addAccessMethod('rtna_cadet_data_manager', 'drop');
		
	}

	private function setAction(){
	}
}
?>
