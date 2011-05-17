<?php
execute_add_extended_class('peopleinfo', 'info', 'Information');

include_once('InformationModel.class.inc');
include_once('peopleinfo.tool.inc');

class Information extends Control{
	function Information(){
		$this->moduleTitle = tt('Information');
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'info';
		$this->tableName = 'information';
		$this->setAccess();
		$this->init(new InformationModel());
		document_set_path(tt('People Information Center'), 'peopleinfo_summary');
		document_set_path(tt('Information'), 'peopleinfo_info');
	}
	
	public function index(){
		$this->id = (int) gg('id');
		$tag = gg('tag');
		if($this->id) return $this->renderPage();
		elseif(strlen($tag)) return $this->renderTag();
		else return $this->renderSummary();
	}
	
	public function listPage(){
		$this->listMeta->title = tt('List of Information');
		$this->listMeta->mode = 'peopleinfo_info';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->setListWriteIcon(tt('Add Information'), 'peopleinfo_info_write');
		$this->setListEditIcon();
		$this->setListDropIcon();
		return $this->renderListPage();
	}
	
	public function write(){
		return Control::write();
	}
	
	public function renderPeopleInformation($userID){
		
	}
	
	public function renderEventInformation($eventID){
		
	}
	
	private function renderTag(){
	
	}
	
	private function renderSummary(){
	
	}
	
	private function renderPage(){
		
	}
	
	private function setAccess(){
		$this->dropAccessMethod('index');
		
		$this->setAdmin('peopleinfo_admin');
		$this->addAction('peopleinfo_info_list', 'listPage');
		
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('listPage', 'peopleinfo_observer');
	}
}

?>
