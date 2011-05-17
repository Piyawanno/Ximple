<?php
execute_add_extended_class('peopleinfo', 'event', 'Event');

include_once('EventModel.class.inc');
include_once('peopleinfo.tool.inc');

class Event extends Control{
	function Event(){
		$this->moduleTitle = tt('Event');
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'event';
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
		return $this->renderListPage();
	}
	
	public function update(){
		print_r(pp());
	}
	
	public function drop(){
		notify_add_error('Information about Event can not be dropped due to the linked Information.');
		execute_set_db();
	}
	
	public function getDefinedPlace(){
		execute_set_ajax();
		$cluase = 'WHERE section='.SECTION." AND place LIKE '%".gg('wildcard')."%'";
		$place = db_select_single_column('event', 'place', $clause);
		return render_option($place);
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
		
		$this->addAction('peopleinfo_event', 'index');
		$this->addAction('peopleinfo_event_list', 'listPage');
		$this->addAction('peopleinfo_event_get_defined_place', 'getDefinedPlace');
		
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('listPage', 'peopleinfo_observer');
		$this->addAccessMethod('getDefinedPlace', 'peopleinfo_observer');
	}
}

?>
