<?php
execute_add_class('poll', 'Poll');

require('PollModel.class.inc');
require('poll.tool.inc');

class Poll extends Control{
	private $comment;
	
	function Poll(){
		$this->tableName = 'poll';
		$this->moduleName = 'poll';
		$this->moduleTitle = tt('Poll');
		$this->setAccess();
		$this->redirectToIDPage = true;
		$this->init(new PollModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		$this->id = (int) gg('id');
		if($this->id){
			$this->selectByID($this->column);
			count_increase($this->fullModuleName, $this->id);
			if($this->isVotable()) return $this->renderVotePage();
			else return $this->renderResultPage();
		}else{
			return $this->listPage();
		}
	}
	
	public function listPage(){
		document_set_path(tt('List of Polls'));
		$this->selectListPage('WHERE section='.SECTION);
		return $this->renderDefaultListPage();
	}
	
	public function vote(){
		$this->id = (int) gg('id');
		if(isVotable()){
			$choise = (int) gg('choise');
			$this->increaseChoise($choise);
			$this->checkVote($choise);
		}
		execute_set_db();
		document_set_redirect('poll/'.$this->id);
	}
	
	public function embed($data){
		return $data;
	}
	
	public function widget(){
		$this->select(array('name'), "WHERE end_date > '".NOW."'");
		$render = '';
		foreach($this->data as $id => $data){
			$renderArray = array(
				'name' => $data['name'],
				'form' => $this->renderVoteForm($id),
			);
			$render .= render($renderArray, 'poll_widget.tpl', 'poll_widget');
		}
		return $render;
	}
	
	public function embedIcon($description){
		if(authoriy_group('poll_admin')){
			
		}
		return $description;
	}
	
	public function embedForm(){
	
	}
	
	private function isVotable(){
		return ($this->checkPermission() and $this->isVoted());
	}
	
	private function renderVotePage(){
		$poll = $this->renderVoteForm($this->id);
		return $this->renderPage($poll);
	}
	
	private function renderResultPage(){
		$poll = $this->renderResult($this->id);
		return $this->renderPage($poll);
	}
	
	private function renderPage($poll){
		head_add_css('poll.css');
		document_set_path($this->dataByID['name']);
		$this->dataByID['poll'] = $poll;
		$this->dataByID['editable'] = authority_group('poll_admin');
#		$this->initComment();
		$render  = render($this->dataByID, 'poll.tpl', 'poll');
#		$render .= $this->comment->render();
		return $render;
	}
	
	private function renderVoteForm($id){
		require_once(INCLUDE_PATH.'class/QuickFormRender.class.inc');
		$quickForm = new QuickFormRender('poll_vote');
		$clause = 'WHERE poll='.$id;
		$choises = db_select_single_column('poll_choise', 'choise', $clause);
		$quickForm->append('choise', Model::radio('', $choises));
		return $quickForm->render();
	}
	
	private function renderResult($id){
		$clause = 'WHERE poll='.$id;
		$column = array('choise', 'vote_number');
		$choises = db_select('poll_choise', $column, $clause);
		$renderArray = array('choises' => $choises);
		return render($renderArray, 'poll_result.tpl', 'poll_result');
	}
	
	private function checkPermission(){
		$permission = $this->dataByID['permission'];
		if($permission == POLL_PERMISSION_ALL){
			return true;
		}elseif($permission == POLL_PERMISSION_AUTHENTICATED){
			return !authority_is_guest();
		}else{
			return authority_group('poll_voter');
		}
	}
	
	private function isVoted(){
		$clause = 'WHERE poll='.$this->id;
		if(authority_is_guest()){
			$ip = poll_get_ip();
			$clause .= " AND voter=-1 AND voter_ip='$ip'";
		}else{
			$clause .= ' AND voter='.USER_ID;
		}
		$vote = db_select_single_column('poll_vote', 'id', $clause);
		return (count($vote) == 0);
	}
	
	private function increaseChoise($choise){
		$clause = 'WHERE id='.$choise;
		$count = db_select_single_column('poll_choise', 'voted_number', $clause);
		$data = array('voted_number' => $count[$choise] + 1);
		db_update('poll_choise', $data, $choise);
	}
	
	private function checkVote($choise){
		$data = array(
			'voter' => USER_ID,
			'voter_ip' => poll_get_ip(),
		);
		db_update('poll_vote', $data, $choise);
	}
	
	private function initComment(){
		include_once(MODULE_PATH.'comment/Comment.class.inc');
		$this->comment = new Comment();
		$this->comment->setMode($this->fullModuleName);
		$this->comment->setParent($this->id);
		$this->comment->setPermission(XIMPLE_COMMENT_ALL);
		$this->comment->setParentWriter($this->dataByID['owner']['id']);
		$this->comment->init();
	}
	
	private function setAccess(){
		$this->setAdmin('poll_admin');
		
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'vote');
		$this->addAccessMethod('guest', 'embed');
		$this->addAccessMethod('guest', 'widget');
		$this->addAccessMethod('guest', 'embedWriteIcon');
		
		$this->addAction('poll_vote', 'vote');
		$this->addAction('poll_embed', 'embed');
		$this->addAction('poll_embed_icon', 'embedIcon');
		$this->addAction('poll_embed_form', 'embedForm');
		$this->addAction('poll_widget', 'widget');
	}
}
?>
