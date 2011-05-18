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
		elseif(strlen($tag)) return $this->renderTag($tag);
		else return $this->renderListPage();
	}
	
	public function renderListPage(){
		$this->listMeta->title = tt('List of Event');
		$this->listMeta->mode = 'peopleinfo_event_list';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->setListWriteIcon(tt('Add Event'), 'peopleinfo_event_write');
		$this->setListEditIcon();
		return Control::renderListPage();
	}
	
	public function insert(){
		Control::insert();
		freetag_update(pp('freetag'), 'peopleinfo_event', $this->id);
		document_set_redirect('peopleinfo_event/'.$this->id);
	}
	
	public function update(){
		Control::update();
		freetag_update(pp('freetag'), 'peopleinfo_event', $this->id);
		document_set_redirect('peopleinfo_event/'.$this->id);
	}
	
	public function getDefinedPlace(){
		execute_set_ajax();
		$cluase = 'WHERE section='.SECTION." AND place LIKE '%".gg('wildcard')."%'";
		$place = db_select_single_column('event', 'place', $clause);
		return render_option($place);
	}
	
	private function renderTag($tag){
		$data = peopleinfo_get_tagged($tag, 'peopleinfo_event', 'event', 'event');
		$renderArray = array(
			'data' => $data,
			'module' => $this->moduleTitle,
			'mode' => 'peopleinfo_event',
			'tag' => $tag
		);
		return render($renderArray, 'peopleinfo_tag_list.tpl', 'peopleinfo_tag_list_event');
	}
	
	private function renderPage(){
		$this->selectByID($this->column);
		$information = new Information(false);
		$renderData = array(
			'data' => $this->dataByID,
			'information' => $information->renderEventInformation($this->id),
			'editable' => authority_group('peopleinfo_admin'),
		);
		head_add_css('peopleinfo.css');
		search_set_page();
		document_set_path($this->dataByID['event']);
		document_add_keywords($this->dataByID['freetag']);
		return render($renderData, 'event.tpl', 'peopleinfo_event');
	}
	
	private function setAccess(){
		$this->dropAction('drop');
		$this->dropAccessMethod('index');
		$this->setAdmin('peopleinfo_admin');
		$this->addAction('peopleinfo_event_get_defined_place', 'getDefinedPlace');
		
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('getDefinedPlace', 'peopleinfo_observer');
	}
}

?>
