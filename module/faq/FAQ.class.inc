<?php
execute_add_class('faq', 'FAQ');
include('FAQModel.class.inc');

class FAQ extends Control{
	function FAQ(){
		$this->moduleTitle = tt('FAQ');
		$this->moduleName = 'faq';
		$this->tableName = 'faq';
		$this->setAction();
		$this->setAccess();
		document_set_path($this->moduleTitle, $this->moduleName);
		$this->init(new FAQModel());
	}
	
	public function index(){
		$clause = 'WHERE section='.SECTION.' AND status=1';
		$this->select($this->column, $clause);
		$renderArray = array(
			'data' => $this->data,
		);
		head_add_css('faq.css');
		return render($renderArray, 'faq.tpl', 'faq');
	}
	
	public function contributorListPage(){
		$title = tt('List of My FAQ');
		document_set_path($title);
		$this->listMeta->title = $title;
		$this->listMeta->mode = 'faq_contributor_list';
		$this->isOwnerMode = true;
		$this->setListWriteIcon();
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (owner='.USER_ID.')');
		return Control::renderListPage();
	}
	
	private function setAction(){
		$this->addAction('faq_contributor_list', 'contributorListPage');
	}
	
	private function setAccess(){
		$this->setAdmin('faq_admin');
		$this->setOwnerColumn('owner');
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('faq_contributor', 'write');
		$this->addAccessMethod('faq_contributor', 'insert');
		$this->addAccessMethod('faq_contributor', 'contributorListPage');
	}
}
?>
