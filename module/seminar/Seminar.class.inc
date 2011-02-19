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
		$this->listMeta->defaultOrder = 'createdate';
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
	
	public function insertMap(){
		if($this->checkFull()){
			$data = array(
				'seminar' => gg('id'),
				'attendant' => USER_ID 
			);
			db_insert('seminar_map', $data);
			execute_set_db(); //after insert coz no display.
			document_set_redirect('seminar_mylist');
			notify_add_info(tt('You have been added to the seminar.'));
		}
	}
	
	private function setAccess(){
		$access = cc('seminar_access');
		$this->addAccessMethod('guest', 'index');
		
//		$this->addAccessMethod('seminar_attendant', 'insertMap');
		$this->addAccessMethod('seminar_admin', 'insertMap');
		
		$this->addAccessMethod('seminar_organizer', 'insert');
		$this->addAccessMethod('seminar_organizer', 'listMyPage');
		
		$this->addAccessMethod('seminar_moderator', 'listPage');
	}
	
	private function setAction(){
//		$this->addAction('seminar_list', 'listPage');
		$this->addAction('seminar_mylist', 'listMyPage');
		$this->addAction('seminar_display', 'display');
		$this->addAction('seminar_insert_map', 'insertMap');
	}
	
	private function checkFull(){
		return true;
	}
	
}
?>
