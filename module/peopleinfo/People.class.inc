<?php
execute_add_class('peopleinfo', 'People');

include_once(ROOT_PATH.'module/freetag/freetag.tool.inc');
include_once('PeopleModel.class.inc');
include_once('peopleinfo.tool.inc');

class People extends Control{
	function People(){
		$this->moduleTitle = tt('People');
		$this->moduleName = 'peopleinfo';
		$this->tableName = 'people';
		$this->setAdmin('peopleinfo_admin');
		$this->init(new PeopleModel());
		document_set_path(tt('People'), 'peopleinfo');
	}
	
	public function index(){
		if(gg('id')) return $this->renderPage();
		else return $this->renderAdminListPage();
	}
	
	public function write(){
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
	
	private function renderPage(){
	
	}
	
	private function renderAdminListPage(){
		$this->listMeta->title = tt('List of People recorded in People Information Center');
		$this->listMeta->mode = 'peopleinfo';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->setListWriteIcon(tt('Add User to People Information Center'), 'peopleinfo_write');
		$this->setListEditIcon();
		$this->setListDropIcon();
		return $this->renderListPage();
	}
}

?>
