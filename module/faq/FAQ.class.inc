<?php
execute_add_class('faq', 'FAQ');
include('FAQModel.class.inc');

class FAQ extends Control{
	function FAQ(){
		$this->moduleTitle = tt('FAQ');
		$this->moduleName = 'faq';
		$this->tableName = 'faq';
		$this->setAccess();
		$this->setAction();
		$this->setAdmin('faq_admin');
		$this->init(new FAQModel());
		document_set_path($this->moduleTitle, $this->moduleName);
		$this->writeLabel = tt('welcom to FAQ');
	}
	
	function index(){
		return 'Index test';
	}
	
	public function arrange(){
		return 'Arrange - Under Construction';
	}
	
	public function listPage(){
		return 'List - Under Construction';
	}
	
	public function display(){
		return 'Display - Under Construction';
	}
	
	private function setAccess(){
		$this->addAccessMethod('guest', 'display');
		$this->addAccessMethod('faq_moderator', 'write');
		$this->addAccessMethod('faq_moderator', 'listPage');
	}
	
	private function setAction(){
		$this->addAction('faq_arrange', 'arrange');
		$this->addAction('faq_display', 'display');
	}
}
?>
