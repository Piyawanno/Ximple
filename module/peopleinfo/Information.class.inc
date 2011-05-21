<?php
execute_add_extended_class('peopleinfo', 'info', 'Information');

include_once('InformationModel.class.inc');
include_once('peopleinfo.tool.inc');

class Information extends Control{
	function Information($setPath=true){
		$this->moduleTitle = tt('Information');
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'info';
		$this->tableName = 'information';
		$this->setAccess();
		$this->init(new InformationModel());
		if($setPath){
			document_set_path(tt('People Information Center'), 'peopleinfo_summary');
			document_set_path(tt('Information'), 'peopleinfo_info');
		}
	}
	
	public function index(){
		$this->id = (int) gg('id');
		$tag = gg('tag');
		if($this->id) return $this->renderPage();
		elseif(strlen($tag)) return $this->renderTag();
		else return $this->renderListPage();
	}
	
	public function renderListPage(){
		document_set_path(tt('List of Information'));
		$this->listMeta->title = tt('List of Information');
		$this->listMeta->mode = 'peopleinfo_info_list';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->setListWriteIcon(tt('Add Information'), 'peopleinfo_info_write');
		$this->setListEditIcon();
		$this->setListDropIcon();
		return Control::renderListPage();
	}
	
	public function write(){
		$this->setConfigForm();
		return Control::write();
	}
	
	public function edit(){
		$this->setConfigForm();
		return Control::edit();
	}
	
	public function insert(){
		print_r(pp());
		Control::insert();
		freetag_update(pp('freetag'), 'people_info', $this->id);
		document_set_redirect('peopleinfo_info');
	}
	
	public function update(){
		Control::update();
		freetag_update(pp('freetag'), 'people_info', $this->id);
		document_set_redirect('peopleinfo_info');
	}
	
	public function renderPeopleInformation($peopleID){
		
	}
	
	public function renderEventInformation($eventID){
		
	}
	
	private function renderTag($tag){
		$data = peopleinfo_get_tagged($tag, 'peopleinfo_info', 'information', 'topic');
		$renderArray = array(
			'data' => $data,
			'module' => $this->moduleTitle,
			'mode' => 'peopleinfo_info',
			'tag' => $tag
		);
		return render($renderArray, 'peopleinfo_tag_list.tpl', 'peopleinfo_tag_list_information');
	}
	
	private function renderPage(){
		
	}
	
	private function setAccess(){
		$this->dropAccessMethod('index');
		$this->setAdmin('peopleinfo_admin');
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('listPage', 'peopleinfo_observer');
	}
	
	private function setConfigForm(){
		$people = $this->getNewConfigForm(tt('related people'));
		$people->append('people');
		
		$event = $this->getNewConfigForm(tt('related events'));
		$event->append('event');
		
		$file = $this->getNewConfigForm(tt('related files'));
		$file->append('file');
	}
}
?>
