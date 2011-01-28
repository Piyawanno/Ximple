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
	}
	
	public function index(){
		return $page;
	}
	
	public function listPage(){
		document_set_path(tt('List of Review for ID'.gg('id')));
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'createdate';
		$this->listMeta->mode = $mode;
		$this->setListWriteIcon(tt('Add new Review'), 'review_write/'.gg('id'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20, 'WHERE (section='.SECTION.') AND (reviewee='.gg('id').')');
		foreach($this->data as $key => $value){
			$this->data[$key]['reviewer'] = render_profile_link($value['reviewer']);
		}
		return $this->renderListPage();
	}
	
	public function listMyPage(){
	
		$selectClause = 'WHERE section='.SECTION." AND reviewer='".$this->owner."'";
		$this->select(array('reviewee', 'star', 'description'), $selectClause);
		foreach($this->data as $key => $value){
			$this->data[$key]['reviewer'] = render_profile_link($value['reviewer']);
		}
		$renderArray = array(
			'review_data' => $this->data
		);
		$page = render($renderArray, 'reviewdisplay.tpl', 'show_faq');
		return $page;
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('review_list/'.pp('reviewee'));
	}
	
	public function write(){
		if(strlen(gg('id')) == 0 or gg('id') == 0){
			notify_add_error(tt('Please choose reviewee before review.'));
			execute_set_db();
			document_set_redirect('review_list');
		}
		else{
			$userInfo = userinfo_get_info_by_id(gg('id'));
			$this->writeLabel = sprintf(tt('Submit new Review for %s'), $userInfo['login_name']);
			return Control::write();
		}
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
