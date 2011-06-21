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
	}
	
	function index(){
		head_add_css('faq.css');
		$clause = 'WHERE section='.SECTION.' AND status=1';
		$this->select($this->column, $clause);
		$category = array();
		$data = array();
		foreach($this->data as $key => $value){
			$cid = $value['category']['id'];
			$category[$cid] = $value['category'];
			$data[$cid][$key] = $value;
			
		}
		$renderArray = array(
			'data' => $data,
			'category' => $category
		);
		$page = render($renderArray, 'faq.tpl', 'show_faq');
		return $page;
	}
	
	public function arrange(){
		return 'Arrange - Under Construction';
	}
	
	public function listPage(){
		document_set_path(tt('List of FAQ'));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'category';
		$this->setListWriteIcon(tt('Add new FAQ'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.')');
		return $this->renderListPage();
	}
	
	private function setAccess(){
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('faq_contributor', 'write');
		$this->addAccessMethod('faq_contributor', 'insert');
		$this->addAccessMethod('faq_contributor', 'edit');
		$this->addAccessMethod('faq_contributor', 'update');
		$this->addAccessMethod('faq_contributor', 'drop');
		$this->addAccessMethod('faq_contributor', 'listPage');
	}
	
	private function setAction(){
		$this->addAction('faq_arrange', 'arrange');
	}
}
?>
