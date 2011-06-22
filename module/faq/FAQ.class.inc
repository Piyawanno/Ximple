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
	
	public function index(){
		head_add_css('faq.css');
		$clause = 'WHERE section='.SECTION.' AND status=1 AND category!=0 ';
		$clause.= 'ORDER BY sort_number';
		$this->select($this->column, $clause);
		$this->translateData();
		$renderArray = array(
			'write_icon' => $this->renderWriteIcon(),
			'data' => $this->processRenderData(),
			'category' => $this->processCategory(),
		);
		return render($renderArray, 'faq.tpl', 'faq');
	}
	
	public function arrange(){
		head_add_css('list.css');
		head_add_css('form.css');
		$clause = 'WHERE section='.SECTION.' ORDER BY sort_number';
		$column = array('id', 'question', 'sort_number', 'category');
		$this->select($column, $clause);
		$clause = "WHERE mode='faq' AND section=".SECTION;
		$category = db_select_single_column('category', 'category', $clause);
		$category[0] = tt('Disable');
		$renderArray = array(
			'write_icon' => $this->renderWriteIcon(),
			'data' => $this->processArrangeData(),
			'category' => $category,
		);
		return render($renderArray, 'faq_arrange.tpl', 'faq_arrange');
	}
	
	public function saveArrange(){
		document_set_redirect('faq');
		execute_set_db();
		$category = pp('category');
		$faq = pp('faq');
		foreach($faq as $key => $value){
			$data = array(
				'category' => $category[$key],
				'sort_number' => $key,
			);
			db_update('faq', $data, $value);
		}
	}
	
	public function listPage(){
		document_set_path(tt('List of FAQ'));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'category';
		$this->setListWriteIcon(tt('Write new Question & Answer'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.')');
		return $this->renderListPage();
	}
	
	private function processRenderData(){
		$data = array();
		foreach($this->data as $key => $value){
			$cid = $value['category']['id'];
			$this->setOwner($value['owner']);
			$data[$cid][$key] = $value;
			$data[$cid][$key]['editable'] = $this->isCallable('edit');
			$data[$cid][$key]['dropable'] = $this->isCallable('drop');
		}
		return $data;
	}
	
	private function processArrangeData(){
		$data = array();
		foreach($this->data as $key => $value){
			$cid = $value['category']['id'];
			$data[$cid][$value['sort_number']] = $value;
		}
		return $data;
	}
	
	private function processCategory(){
		$category = array();
		foreach($this->data as $key => $value){
			$cid = $value['category']['id'];
			$category[$cid] = $value['category']['category'];
		}
		return $category;
	}
	
	private function setAccess(){
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('faq_contributor', 'write');
		$this->addAccessMethod('faq_contributor', 'insert');
		$this->ownerColumn = 'owner';
	}
	
	private function setAction(){
		$this->addAction('faq_arrange', 'arrange');
		$this->addAction('faq_save_arrange', 'saveArrange');
	}
	
	private function renderWriteIcon(){
		if($this->isCallable('write')){
			return render_write_icon('faq_write', tt('Write new Question & Answer'));
		}
	}
}
?>
