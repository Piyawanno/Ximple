<?php
execute_add_class('seminar', 'Seminar');
include('SeminarModel.class.inc');

class Seminar extends Control{
	function Seminar(){
		$this->moduleTitle = tt('Seminar');
		$this->moduleName = 'seminar';
		$this->tableName = 'seminar';
		$this->setAccess();
		$this->setAction();
		$this->setAdmin('seminar_admin');
		$this->init(new SeminarModel());
		document_set_path($this->moduleTitle, $this->moduleName);
		$this->writeLabel = tt('Submit new seminar');
	}
	
	public function index(){
		if(authority_group('seminar_moderator') or authority_group('seminar_admin')){
			document_set_path(tt('Seminar Summerize'));
			head_add_css('list.css');
			$page = render($renderArray, 'seminarreport.tpl', 'seminar_seminarreport');
		}else{
			$page = render($renderArray, 'seminar_seminarreport_reporter.tpl', 'seminar_seminarreport');
		}
		return $page;
	}
	
	public function listPage(){
		document_set_path(tt('List of Seminar'));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'size';
		if(mid()) $mode = mm().'/'.mid();
		else $mode = mm();
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new Seminar'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.')');
		return $this->renderListPage();
	}
	
	public function listMyPage(){
		document_set_path(tt('List of My Seminar'));
		$this->listMeta->title = sprintf(tt('List of My %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'createdate';
		if(mid()) $mode = mm().'/'.mid();
		else $mode = mm();
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new Seminar'));
		$this->modelConnector->setAttribute('size', 'isList', false);
		$this->modelConnector->setAttribute('classdate', 'isList', false);
		$this->selectListPage(20, 'WHERE (owner='.USER_ID.')');
		return $this->renderListPage();
	}
	
	public function display(){
		document_set_path(tt('Display'));
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		head_add_css('list.css');
		$renderArray = array(
			'data' => $this->data[$this->id],
		);
		if(authority_group('seminar_moderator') or authority_group('seminar_admin'))
			$render = render($renderArray, 'seminardisplay.tpl', 'seminardisplay');
		else
			$render = render($renderArray, 'seminardisplay_attendant.tpl', 'seminardisplay');
		return $render;
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('seminar_display/'.$this->id);
	}
	
	private function setAccess(){
		$access = cc('seminar_access');
		if($access == 0){
			$this->addAccessMethod('guest', 'index');
			$this->addAccessMethod('guest', 'write');
			$this->addAccessMethod('guest', 'insert');
		}elseif($access == 1){
			$this->addAccessMethod('user', 'index');
			$this->addAccessMethod('user', 'write');
			$this->addAccessMethod('user', 'insert');
		}else{
			$this->addAccessMethod('seminar_seminarr', 'index');
			$this->addAccessMethod('seminar_seminarr', 'write');
			$this->addAccessMethod('seminar_seminarr', 'insert');
			$this->addAccessMethod('seminar_seminarr', 'listMyPage');
		}
		$this->addAccessMethod('seminar_moderator', 'listPage');
		$this->addAccessMethod('seminar_moderator', 'listMyPage');
	}
	
	private function setAction(){
//		$this->addAction('seminar_list', 'listPage');
		$this->addAction('seminar_mylist', 'listMyPage');
		$this->addAction('seminar_display', 'display');
	}
	
}
?>
