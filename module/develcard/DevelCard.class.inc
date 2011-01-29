<?php
execute_add_class('develcard', 'DevelCard');
include('DevelCardModel.class.inc');

class DevelCard extends Control{
	function DevelCard(){
		$this->moduleTitle = tt('DevelCard');
		$this->moduleName = 'develcard';
		$this->tableName = 'develcard';
		$this->setAccess();
		$this->setAction();
		$this->setAdmin('develcard_admin');
		$this->init(new DevelCardModel());
		document_set_path($this->moduleTitle, $this->moduleName);
		$this->writeLabel = tt('Submit new DevelCard');
	}
	
	public function index(){
//		head_add_js('module/develcard/systemtheme/bluff-min.js');
//		head_add_js('module/develcard/systemtheme/excanvas.js');
		if(authority_group('develcard_moderator') or authority_group('develcard_admin')){
			document_set_path(tt('DevelCard Summerize'));
			head_add_css('list.css');
//			$result = db_select($this->tableName, this->column, 'WHERE id='.(int)$this->id);
//			$renderArray = array(
//			'data' => $this->data
//		);
			$page = render($renderArray, 'develcardreport.tpl', 'develcardreport');
		}else{
			$page = render($renderArray, 'develcardreport_reporter.tpl', 'develcardreport');
		}
		return $page;
	}
	
	public function listPage(){
		document_set_path(tt('List of DevelCard'));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'priority';
		if(mid()) $mode = mm().'/'.mid();
		else $mode = mm();
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new Develcard'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.')');
		return $this->renderListPage();
	}
	
	public function listMyPage(){
		document_set_path(tt('List of My DevelCard'));
		$this->listMeta->title = sprintf(tt('List of My %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'createdate';
		if(mid()) $mode = mm().'/'.mid();
		else $mode = mm();
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new Develcard'));
		$this->modelConnector->setAttribute('priority', 'isList', false);
		$this->modelConnector->setAttribute('deadline', 'isList', false);
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
		if(authority_group('develcard_moderator') or authority_group('develcard_admin'))
			$render = render($renderArray, 'develcarddisplay.tpl', 'develcarddisplay');
		else
			$render = render($renderArray, 'develcarddisplay_reporter.tpl', 'develcarddisplay');
		return $render;
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('develcard_display/'.$this->id);
	}
	
	private function setAccess(){
		$access = cc('develcard_access');
		if($access == 0){
			$this->addAccessMethod('guest', 'index');
			$this->addAccessMethod('guest', 'write');
			$this->addAccessMethod('guest', 'insert');
		}elseif($access == 1){
			$this->addAccessMethod('user', 'index');
			$this->addAccessMethod('user', 'write');
			$this->addAccessMethod('user', 'insert');
		}else{
			$this->addAccessMethod('develcard_reporter', 'index');
			$this->addAccessMethod('develcard_reporter', 'write');
			$this->addAccessMethod('develcard_reporter', 'insert');
			$this->addAccessMethod('develcard_reporter', 'listMyPage');
		}
		$this->addAccessMethod('develcard_moderator', 'listPage');
		$this->addAccessMethod('develcard_moderator', 'listMyPage');
	}
	
	private function setAction(){
//		$this->addAction('develcard_list', 'listPage');
		$this->addAction('develcard_mylist', 'listMyPage');
		$this->addAction('develcard_display', 'display');
	}
	
}
?>
