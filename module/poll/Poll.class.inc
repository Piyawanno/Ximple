<?php
execute_add_class('poll', 'Poll');

require('PollModel.class.inc');
require('poll.tool.inc');

class Poll extends Control{
	function Poll(){
		$this->tableName = 'poll';
		$this->moduleName = 'poll';
		$this->moduleTitle = tt('Poll');
		$this->setAccess();
		$this->init(new PollMode());
	}
	
	public function index(){
	
	}
	
	public function listPage(){
	
	}
	
	public function vote(){
	
	}
	
	public function embed(){
	
	}
	
	public function widget(){
	
	}
	
	private function renderVoteForm(){
	
	}
	
	private function renderResult(){
	
	}
	
	private function setAccess(){
		$this->setAdmin('poll_admin');
		
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'vote');
		$this->addAccessMethod('guest', 'embed');
		$this->addAccessMethod('guest', 'widget');
		
		$this->addAction('poll_vote', 'vote');
		$this->addAction('poll_embed', 'embed');
		$this->addAction('poll_widget', 'widget');
	}
}
?>
