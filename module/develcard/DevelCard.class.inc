<?php
execute_add_class('develcard', 'DevelCard');
include('DevelCardModel.class.inc');
include('develcard.tool.inc');

class DevelCard extends Control{
	function DevelCard(){
		$this->moduleTitle = tt('DevelCard');
		$this->moduleName = 'develcard';
		$this->tableName = 'develcard';
		$this->setAccess();
		$this->setAction();
		$this->setAdmin('develcard_admin');
		$this->redirectToIDPage = true;
		$this->init(new DevelCardModel());
		$this->setConfig();
		$this->writeLabel = tt('Submit new DevelCard');
		document_set_path($this->moduleTitle, $this->moduleName);
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
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new Develcard'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.')');
		return $this->renderListPage();
	}
	
	public function reporterListPage(){
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
		$this->id = (int) gg('id');
		$this->selectByID($this->column);
		
		$renderArray = array(
			'data' => $this->dataByID,
		);
		$render = render($renderArray, 'develcarddisplay.tpl', 'develcarddisplay');
		return $render;
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
		}
		
		$this->addAccessMethod('develcard_reporter', 'index');
		$this->addAccessMethod('develcard_reporter', 'write');
		$this->addAccessMethod('develcard_reporter', 'insert');
		$this->addAccessMethod('develcard_reporter', 'reporterListPage');
		
		$this->addAccessMethod('develcard_moderator', 'index');
		$this->addAccessMethod('develcard_moderator', 'write');
		$this->addAccessMethod('develcard_moderator', 'insert');
		$this->addAccessMethod('develcard_moderator', 'listPage');
		$this->addAccessMethod('develcard_moderator', 'reporterListPage');
	}
	
	private function setAction(){
		$this->addAction('develcard_list', 'listPage');
		$this->addAction('develcard_reporter_list', 'reporterListPage');
		$this->addAction('develcard_display', 'display');
	}
	
	private function setConfig(){
		$config = $this->getNewConfigForm(tt('Work Flow & Configuration'));
		$config->append('priority');
		$config->append('status');
		$config->append('resolver');
		$config->append('deadline');
	}
}
?>
