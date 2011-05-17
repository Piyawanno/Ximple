<?php
execute_add_class('peopleinfo', 'People');

include_once(ROOT_PATH.'module/freetag/freetag.tool.inc');
include_once('PeopleModel.class.inc');
include_once('Information.class.inc');
include_once('peopleinfo.tool.inc');

class People extends Control{
	function People(){
		$this->moduleTitle = tt('People');
		$this->moduleName = 'peopleinfo';
		$this->tableName = 'people';
		$this->setAccess();
		$this->init(new PeopleModel());
		document_set_path(tt('People Information Center'), 'peopleinfo_summary');
		document_set_path(tt('People'), 'peopleinfo');
	}
	
	public function index(){
		$this->id = (int) gg('id');
		$tag = gg('tag');
		if($this->id) return $this->renderPage();
		elseif(strlen($tag)) return $this->renderTag();
		else return $this->renderSummary();
	}
	
	public function renderMainSummary(){
	
	}
	
	public function listPage(){
		$this->listMeta->title = tt('List of People recorded in People Information Center');
		$this->listMeta->mode = 'peopleinfo';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->data = userinfo_get_login_name($this->data, 'people');
		$this->setListWriteIcon(tt('Add User to People Information Center'), 'peopleinfo_write');
		$this->setListEditIcon();
		$this->setListDropIcon();
		return $this->renderListPage();
	}
	
	public function write(){
		if($this->checkRelatedGroup()){
			head_add_css('peopleinfo.css');
			head_add_js('module/peopleinfo/peopleinfo.js');
			head_add_js('include/external/sha1.js');
		
			$description  = tt("Only User with the Role of 'People Information Related' can be inserted into database. ");
			$description .= sprintf(tt('You can use <a href="%s">User Management</a> to add the Role to Users.'), SECTION_URI.Q.'user');
		
			$this->formMeta->description  = render_ajax_icon('addPeopleUser', 'files/icon/add.png', tt('Add new User'));
			$this->formMeta->description .= '<p>'.$description.'</p>';
			$form  = Control::write();
			$form .= '<div id="peopleinfo_user_dialog" title="'.tt('Add new User').'"></div>';
			return $form;
		}
	}
	
	public function edit(){
		$userInfo = userinfo_get_info_by_id($this->dataByID['people']);
		$this->editLabel = tt('Edit People Information').' : '.$userInfo['login_name'];
		return Control::edit();
	}
	
	public function insert(){
		Control::insert();
		freetag_update(pp('freetag'), 'people', $this->id);
	}
	
	public function update(){
		Control::update();
		freetag_update(pp('freetag'), 'people', $this->id);
	}
	
	private function checkRelatedGroup(){
		if(count(cc('peopleinfo_related')) == 0){
			$pattern = tt('A group with the role of "People Information Related" should be created (<a href="%s">Group Management</a>)');
			notify_add_error(sprintf($pattern, SECTION_URI.Q.'group'));
			execute_set_db();
			document_set_redirect('peopleinfo_list');
			return false;
		}
		return true;
	}
	
	private function renderTag(){
	
	}
	
	private function renderSummary(){
	
	}
	
	private function renderPage(){
		$this->selectByID($this->column);
		$information = new Information();
		$this->dataByID['people'] = userinfo_get_info_by_id($this->dataByID['people']);
		$renderData = array(
			'data' => $this->dataByID,
			'information' => $information->renderPeopleInformation($this->dataByID['people']['id']),
		);
		document_set_path($this->dataByID['people']['login_name']);
		return render($renderData, 'people.tpl', 'peopleinfo_people');
	}
	
	private function setAccess(){
		$this->dropAccessMethod('index');
		
		$this->setAdmin('peopleinfo_admin');
		$this->setOwner('people');
		
		$this->addAction('peopleinfo_list', 'renderListPage');
		$this->addAction('peopleinfo_summary', 'renderMainSummary');
		
		$this->addAccessMethod('listPage', 'peopleinfo_observer');
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('renderMainSummary', 'peopleinfo_observer');
	}
	
}

?>
