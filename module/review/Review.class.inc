<?php
execute_add_class('review', 'Review');
include('ReviewModel.class.inc');

class Review extends Control{
	function Review(){
		$this->moduleTitle = tt('Review');
		$this->moduleName = 'review';
		$this->tableName = 'review';
		$this->setAccess();
		$this->setAction();
		$this->setAdmin('review_admin');
		$this->init(new ReviewModel());
		document_set_path($this->moduleTitle, $this->moduleName);
		$this->writeLabel = tt('Submit new Review');
	}
	
	public function index(){
		return $page;
	}
	
	public function listPage(){
		$this->id = MODE_ID;
		document_set_path(tt('List of Review for ID'.$this->id));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'createdate';
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new Review'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.') AND (toid='.$this->id.')');
		return $this->renderListPage();
	}
	
	public function listMyPage(){
		document_set_path(tt('List of My Review'));
		$this->listMeta->title = sprintf(tt('List of My %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'createdate';
		$this->listMeta->mode = $mode;
#		$this->modelConnector->setAttribute('priority', 'isList', false);
#		$this->modelConnector->setAttribute('deadline', 'isList', false);
		$this->selectListPage(20, 'WHERE (owner='.USER_ID.') AND (section='.SECTION.')');
		return $this->renderListPage();
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('review_listPage/'.$this->id);
	}
	
	private function setAccess(){
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('review_reviewer', 'write');
		$this->addAccessMethod('review_reviewer', 'insert');
		$this->addAccessMethod('review_reviewer', 'listMyPage');
		$this->addAccessMethod('review_reviewer', 'listPage');
	}
	
	private function setAction(){
//		$this->addAction('review', 'index');
//		$this->addAction('review_write', 'write');
//		$this->addAction('review_list', 'listPage');
		$this->addAction('review_mylist', 'listMyPage');
//		$this->addAction('review_manage', 'manage');
	}
	
}
execute_add_function('review_add_link');
function review_add_link($params, $result){
	$result[] = array(
		'mode' => 'review_list/'.$params['id'],
		'icon' => 'review/theme/test.png',
		'label' => sprintf(tt('show all reviews of %s'),$params['login_name']),
	);
	return $result;
}
?>
