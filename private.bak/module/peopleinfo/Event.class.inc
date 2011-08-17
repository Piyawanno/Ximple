<?php
execute_add_extended_class('peopleinfo', 'event', 'Event');

include_once('Information.class.inc');
include_once('EventModel.class.inc');
include_once('peopleinfo.tool.inc');

class Event extends Control{
	function Event($setPath=true){
		$this->moduleTitle = tt('Event');
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'event';
		$this->tableName = 'event';
		$this->setAccess();
		$this->redirectToIDPage = true;
		$this->init(new EventModel());
		if($setPath){
			document_set_path(tt('People Information Center'), 'peopleinfo_summary');
			document_set_path(tt('Event'), 'peopleinfo_event');
		}
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
		$this->listMeta->mode = 'peopleinfo_event';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->setListWriteIcon(tt('Add Event'), 'peopleinfo_event_write');
		$this->setListEditIcon();
		return Control::renderListPage();
	}
	
	public function renderPlace(){
		if(gg('place')){
			$place = gg('place');
		}else{
			$this->id = (int) gg('id');
			$this->selectByID(array('place'));
			$place = $this->dataByID['place'];
		}
		$this->selectSingleColumn('event', "WHERE place='$place'");
		$renderArray = array(
			'data' => $this->data,
			'place' => $place
		);
		document_set_path($place);
		return render($renderArray, 'peopleinfo_event_place.tpl', 'peopleinfo_event_place');
	}
	
	public function getDefinedPlace(){
		execute_set_ajax();
		$clause = 'WHERE section='.SECTION." AND place LIKE '%".gg('wildcard')."%'";
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
		$this->setOwner($this->dataByID['creator']['id']);
		$information = new Information(false);
		$renderData = array(
			'data' => $this->dataByID,
			'information' => $information->renderEventInformation($this->id),
			'editable' => $this->isCallable('edit'),
		);
		head_add_css('peopleinfo.css');
		search_set_page();
		document_set_path($this->dataByID['event']);
		document_add_keywords($this->dataByID['freetag']);
		return render($renderData, 'peopleinfo_event.tpl', 'peopleinfo_event');
	}
	
	private function setAccess(){
		$this->ownerColumn = 'creator';
		$this->dropAction('drop');
		$this->dropAccessMethod('index');
		$this->setAdmin('peopleinfo_admin');
		$this->addAction('peopleinfo_event_get_defined_place', 'getDefinedPlace');
		$this->addAction('peopleinfo_event_place', 'renderPlace');
		
		$this->addAccessMethod('peopleinfo_observer', 'index');
		$this->addAccessMethod('peopleinfo_observer', 'getDefinedPlace');
		$this->addAccessMethod('peopleinfo_observer', 'rednerPlace');
		
		$this->addAccessMethod('peopleinfo_informant', 'index');
		$this->addAccessMethod('peopleinfo_informant', 'write');
		$this->addAccessMethod('peopleinfo_informant', 'insert');
		$this->addAccessMethod('peopleinfo_informant', 'getDefinedPlace');
		$this->addAccessMethod('peopleinfo_informant', 'rednerPlace');
	}
}

?>
