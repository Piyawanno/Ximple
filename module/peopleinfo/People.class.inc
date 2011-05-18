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
	}
	
	public function index(){
		document_set_path(tt('People'), 'peopleinfo');
		$this->id = (int) gg('id');
		$tag = gg('tag');
		if($this->id) return $this->renderPage();
		elseif(strlen($tag)) return $this->renderTag($tag);
		else return $this->renderListPage();
	}
	
	public function renderMainSummary(){
		head_add_css('peopleinfo.css');
		$clause = 'WHERE section='.SECTION.' ORDER BY update_time DESC LIMIT 10';
		$this->select($this->column);
		$this->data = userinfo_get_info($this->data, 'people');
		
		$event = new Event(false);
		$event->select($event->column, $clause);
		
		$information = new Information(false);
		$information->select($information->column, $clause);
		
		$renderArray = array(
			'people' => $this->data,
			'event' => $event->data,
			'information' => $information->data,
		);
		
		return render($renderArray, 'peopleinfo_summary.tpl', 'peopleinfo_summary');
	}
	
	public function renderTagClound(){
		head_add_css('peopleinfo.css');
		document_set_path(tt('Tag Cloud'));
		require_once(ROOT_PATH.'module/freetag/freetag.tool.inc');
		$tag['people'] = freetag_get('peopleinfo');
		$tag['event'] = freetag_get('peopleinfo_event');
		$tag['information'] = freetag_get('peopleinfo_info');
		return render($tag, 'peopleinfo_tag_cloud.tpl', 'peopleinfo_tag_cloud');
	}
	
	public function renderListPage(){
		$this->listMeta->title = tt('List of People recorded in People Information Center');
		$this->listMeta->mode = 'peopleinfo';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->data = userinfo_get_login_name($this->data, 'people');
		$this->setListWriteIcon(tt('Add User to People Information Center'), 'peopleinfo_write');
		$this->setListEditIcon();
		return Control::renderListPage();
	}
	
	public function write(){
		if($this->checkRelatedGroup()){
			document_set_path(tt('People'), 'peopleinfo');
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
		document_set_path(tt('People'), 'peopleinfo');
		$userInfo = userinfo_get_info_by_id($this->dataByID['people']);
		$this->editLabel = tt('Edit People Information').' : '.$userInfo['login_name'];
		return Control::edit();
	}
	
	public function insert(){
		Control::insert();
		freetag_update(pp('freetag'), 'peopleinfo', $this->id);
		document_set_redirect('peopleinfo/'.$this->id);
	}
	
	public function update(){
		Control::update();
		freetag_update(pp('freetag'), 'peopleinfo', $this->id);
		document_set_redirect('peopleinfo/'.$this->id);
	}
	
	private function checkRelatedGroup(){
		if(count(cc('peopleinfo_related')) == 0){
			notify_add_error(peopleinfo_get_group_warning());
			execute_set_db();
			document_set_redirect('peopleinfo_list');
			return false;
		}
		return true;
	}
	
	private function renderTag($tag){
		$data = peopleinfo_get_tagged($tag, 'peopleinfo', 'people', 'people');
		foreach($data as $key => $value){
			$userInfo = userinfo_get_info_by_id($value);
			$data[$key] = $userInfo['login_name'];
		}
		$renderArray = array(
			'data' => $data,
			'module' => $this->moduleTitle,
			'mode' => 'peopleinfo',
			'tag' => $tag
		);
		return render($renderArray, 'peopleinfo_tag_list.tpl', 'peopleinfo_tag_list_people');
	}
	
	private function renderPage(){
		$this->selectByID($this->column);
		$information = new Information(false);
		$this->dataByID['people'] = userinfo_get_info_by_id($this->dataByID['people']);
		$renderData = array(
			'data' => $this->dataByID,
			'information' => $information->renderPeopleInformation($this->id),
			'editable' => authority_group('peopleinfo_admin'),
		);
		head_add_css('peopleinfo.css');
		search_set_page();
		document_set_path($this->dataByID['people']['login_name']);
		document_add_keywords($this->dataByID['freetag']);
		return render($renderData, 'people.tpl', 'peopleinfo_people');
	}
	
	private function setAccess(){
		$this->dropAction('drop');
		$this->dropAccessMethod('index');
		
		$this->setAdmin('peopleinfo_admin');
		$this->setOwner('people');
		
		$this->addAction('peopleinfo_summary', 'renderMainSummary');
		$this->addAction('peopleinfo_tag_clound', 'renderTagClound');
		
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('renderMainSummary', 'peopleinfo_observer');
		$this->addAccessMethod('renderTagClound', 'peopleinfo_observer');
	}
	
}

?>
