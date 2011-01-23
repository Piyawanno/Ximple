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
		$renderArray = array(
			'name' => 'value',
		);
		$page = render($renderArray, 'develcardreport.tpl', 'develcardreport');
		return $page;
	}
	
	public function listPage(){
		document_set_path(tt('List of DevelCard'));
		$this->selectListPage(20, 'WHERE (section='.SECTION.')',array('type'));
		return $this->renderDefaultListPage();
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
		}
		$this->addAccessMethod('develcard_moderator', 'listPage');
	}
	
	private function setAction(){
		$this->addAction('delvelcard_list', 'listPage');
	}
	
}
?>
