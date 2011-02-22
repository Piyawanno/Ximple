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
		if(authority_group('review_reviewer')) {
			return $this->reviewerList();
		} else {
			return $this->revieweeList();
		}
	}
	
	public function listPage(){ // for admin to manage
		document_set_path(tt('List of all Review'));
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
	
	public function revieweeList(){
#		print_r($this->owner);
#		$selectClause = ' inner join review_rating on review.id = review_rating.reviewId WHERE section='.SECTION." AND reviewee='".gg('id')."'".' ORDER BY CREATEDATE DESC';
#		$pageLength = 10
#		$this->selectPage(array('review.id', 'review.reviewer', 'review.star','review.createdate', 'review.description','review_rating.point'), $pageLength,$selectClause);
		$selectClause = 'WHERE section='.SECTION." AND reviewee='".gg('id')."'".' ORDER BY CREATEDATE DESC';
		$this->select(array('id', 'reviewer', 'star','createdate', 'description'),$selectClause);
		foreach($this->data as $key => $value){
			$this->data[$key]['reviewer'] = render_profile_link($value['reviewer']);
		}
		$renderArray = array(
			'reviewer' => USER_ID,
			'reviewee' => gg('id'),
			'review_data' => $this->data,
		);
		$page = render($renderArray, 'revieweedisplay.tpl', 'show_faq');
		return $page;
	}
	
	public function reviewRating(){
		$data = array(
			'reviewId' => gg('reviewId'),
			'scorer' => (int)gg('scorer'),
			'point' => (int)gg('point'), 
		);
		print_r($data);
		db_insert('review_rating', $data);
		execute_set_db(); //after insert coz no display.
		document_set_redirect('review_reviewee_list/'.gg('id'));
	}
	
	public function reviewerList(){
#		print_r($this->owner);
		$selectClause = 'WHERE section='.SECTION." AND reviewer='".gg('id')."'";
		$this->select(array('reviewee', 'star','createdate', 'description'), $selectClause);
		foreach($this->data as $key => $value){
			$this->data[$key]['reviewee'] = render_profile_link($value['reviewee']);
		}
		$renderArray = array(
			'review_data' => $this->data
		);
		$page = render($renderArray, 'reviewerdisplay.tpl', 'show_faq');
		return $page;
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('review_reviewee_list/'.pp('reviewee'));
	}
	
	public function write(){
		if(strlen(gg('id')) == 0 or gg('id') == 0){
			notify_add_error(tt('Please choose reviewee before review.'));
			execute_set_db();
			document_set_redirect('review_reviewee_list');
		}
		else{
			$userInfo = userinfo_get_info_by_id(gg('id'));
			$this->writeLabel = sprintf(tt('Submit new Review for %s'), $userInfo['login_name']);
			return Control::write();
		}
	}
	
	private function setAccess(){
		$this->addAccessMethod('guest', 'revieweeList');
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('review_reviewer', 'write');
		$this->addAccessMethod('review_reviewer', 'insert');
		$this->addAccessMethod('review_reviewer', 'reviewerList');
		$this->addAccessMethod('review_reviewer', 'reviewRating');
#		$this->addAccessMethod('guest', 'write');
#		$this->addAccessMethod('guest', 'insert');
	}
	
	private function setAction(){
//		$this->addAction('review', 'index');
//		$this->addAction('review_write', 'write');
//		$this->addAction('review_list', 'listPage');
		$this->addAction('review_reviewer_list', 'reviewerList');
		$this->addAction('review_reviewee_list', 'revieweeList');
		$this->addAction('review_rating', 'reviewRating');
//		$this->addAction('review_manage', 'manage');
	}
	
}
execute_add_function('review_add_link');
function review_add_link($params, $result){
	// ?? if selected profile is reviewee
	$result[] = array(
		'mode' => 'review_reviewee_list/'.$params['id'],
		'icon' => 'review/theme/test.png',
		'label' => sprintf(tt('show all reviews of %s'),$params['login_name']),
	);
	// ?? if selected profile is reviewer do nothing
	return $result;
}
?>
