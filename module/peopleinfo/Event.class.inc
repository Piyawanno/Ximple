<?php
execute_add_extended_class('peopleinfo', 'event', 'Event');

include_once('EventModel.class.inc');
include_once('peopleinfo.tool.inc');

class Event extends Control{
	function Event(){
		$this->moduleTitle = tt('Event');
		$this->moduleName = 'peopleinfo';
		$this->tableName = 'event';
		$this->setAccess();
		$this->init(new EventModel());
		document_set_path(tt('People Information Center'), 'peopleinfo_summary');
		document_set_path(tt('Event'), 'peopleinfo_event');
		
	}
	
	public function index(){
		$this->id = (int) gg('id');
		$tag = gg('tag');
		if($this->id) return $this->renderPage();
		elseif(strlen($tag)) return $this->renderTag();
		else return $this->renderSummary();
	}
	
	public function listPage(){
		$this->listMeta->title = tt('List of Event');
		$this->listMeta->mode = 'peopleinfo_info';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->setListWriteIcon(tt('Add Event'), 'peopleinfo_event_write');
		$this->setListEditIcon();
		$this->setListDropIcon();
		return $this->renderListPage();
	}
	
	public function write(){
		return Control::write();
	}
	
	private function renderTag(){
	
	}
	
	private function renderSummary(){
	
	}
	
	private function renderPage(){
		
	}
	
	private function setAccess(){
		$this->setAdmin('peopleinfo_admin');
		
		$this->addAction('peopleinfo_event', 'index');
		$this->addAction('peopleinfo_event_list', 'listPage');
		$this->addAction('peopleinfo_event_write', 'write');
		
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('listPage', 'peopleinfo_observer');
	}
}

?>
