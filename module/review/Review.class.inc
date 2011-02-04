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
		$selectClause = "WHERE scorer='".USER_ID."'".' ORDER BY reviewId DESC';
		$rating = db_select('review_rating',array('reviewId'),$selectClause);
		$ratingcount = count($rating);
#		print_r($rating);
		$selectClause = 'WHERE section='.SECTION." AND reviewee='".gg('id')."'".' ORDER BY CREATEDATE DESC';
		$this->data = db_select('review',array('id', 'reviewer', 'star','createdate', 'description', 'point1', 'point2'),$selectClause);
		$total = 0;
		$count = 0;
		$listId = "";
		$ratingId = 0;
		$reviewRatingId = $rating[$ratingId]['reviewId'];
		$renderData = array();
		foreach($this->data as $key => $value){
			$all = ($value['point1'] + $value['point2']);
			$total = $total + ($value['star'] * ($value['point1'] / $all));
			$count++;
			//default not found rating
			if (USER_ID == $value['reviewer']){
				$canReview = false;
			}else{
				$canReview = true;
			}
			
			while (($value['id'] <= $reviewRatingId) && ($ratingId < $ratingcount)){
				$reviewRatingId = $rating[$ratingId]['reviewId'];
				if ($value['id'] == $reviewRatingId){
					//already rating
					$canReview = false;
					break;
				}
				$ratingId++;
			}
			$row = array(
				'id' => $value['id'],
				'reviewer' => $value['reviewer'],
				'reviewerLink' => render_profile_link(userinfo_get_info_by_id($value['reviewer'])),
				'star' => $value['star'],
				'createdate' => $value['createdate'],
				'description' => $value['description'],
				'point1' => $value['point1'],
				'point2' => $value['point2'],
				'canReview' => $canReview
			);
			$renderData[] = $row;
		}
		if ($count == 0){
			$total = 0;
		}else{
			$total = $total/$count;
		}
		$reviewee = userinfo_get_info_by_id(gg('id'));
		$renderArray = array(
			'reviewer' => USER_ID,
			'reviewee' => gg('id'),
			'reviewee_name' => $reviewee['login_name'],
			'total' => $total,
			'review_data' => $renderData,
		);
		$page = render($renderArray, 'revieweedisplay.tpl', 'show_faq');
		return $page;
	}
	
	public function reviewRating(){
		$selectClause = "WHERE reviewId='".gg('reviewId')."' AND scorer='".gg('scorer')."'";
		$foundRating = db_get_rows_number('review_rating',$selectClause);
		if ($foundRating != 0){
			document_set_redirect('review_reviewee_list/'.gg('id'));
			notify_add_info(tt('This review already has been rated by this reviewer'));
		}else{
			$data = array(
				'reviewId' => gg('reviewId'),
				'scorer' => (int)gg('scorer'),
				'point' => (int)gg('point'), 
			);
#			print_r($data);
			db_insert('review_rating', $data);
			execute_set_db(); //after insert coz no display.
			$this->id = gg('reviewId');
			$this->selectByID($this->column);
			$assignedPoint = (int)gg('point');
			$point1 = $this->data[$this->id]['point1'];
			$point2 = $this->data[$this->id]['point2'];
			if ($assignedPoint > 0){
				$point1 = $point1 + $assignedPoint;
			} else {
				$point2 = $point2 - $assignedPoint;
			}
			db_update('review',array('point1' => $point1, 'point2' => $point2),$this->id);
			document_set_redirect('review_reviewee_list/'.gg('id'));	
		}
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
