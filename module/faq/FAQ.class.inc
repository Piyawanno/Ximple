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
		$clause = 'WHERE section='.SECTION." AND mode='faq'";
		$category = db_select_single_column('category', 'category', $clause);
#		$category = db_select('category', array('id', 'category'), $clause);
#		$this->select($this->column, $clause); # select all coulmn
#		print_r($category);
		$selected_category = gg('selected_category');
		$select_clause = 'WHERE section='.SECTION." AND category='$selected_category'";
		$this->select(array('id', 'question', 'answer'), $select_clause);
		$renderArray = array(
			'category' => $category,
			'selected_category' => $selected_category,
			'faq_data' => $this->data
		);
		$page = render($renderArray, 'faqdisplay.tpl', 'show_faq');
		return $page;
	}
	
	public function arrange(){
		return 'Arrange - Under Construction';
	}
	
	public function listPage(){
		document_set_path(tt('List of FAQ'));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'category';
		if(mid()) $mode = mm().'/'.mid();
		else $mode = mm();
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new FAQ'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.')');
#		print_r($this->data);
		foreach($this->data as $key => $value){
			$this->data[$key]['category'] = $value['category']['category'];
		}
		return $this->renderListPage();
	}
	
	private function setAccess(){
		$this->addAccessMethod('faq_moderator', 'write');
		$this->addAccessMethod('faq_moderator', 'listPage');
	}
	
	private function setAction(){
		$this->addAction('faq_arrange', 'arrange');
	}
}
?>
