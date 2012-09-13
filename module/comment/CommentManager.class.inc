<?php
class CommentManager{
	private $module;
	private $permissionColumn;
	private $commentTimeColumn;
	private $ownerColumn;
	private $topicColumn;
	private $uriColumn;
	
	function CommentManager($module){
		$this->module = $module;
	}
	
	public function setPermissionColumn($permissionColumn){
		$this->permissionColumn = $permissionColumn;
	}
	
	public function setCommentTimeColumn($commentTimeColumn){
		$this->commentTimeColumn = $commentTimeColumn;
	}
	
	public function setTopicColumn($topicColumn){
		$this->topicColumn = $topicColumn;
	}
	
	public function setURIColumn($uriColumn){
		$this->uriColumn = $uriColumn;
	}
	
	public function setOwnerColumn($ownerColumn){
		$this->ownerColumn = $ownerColumn;
	}
	
	public function commit(){
		$config = array(
			'comment_permission' => $this->permissionColumn,
			'comment_time' => $this->commentTimeColumn,
			'owner' =>$this->ownerColumn,
			'topic' => $this->topicColumn,
			'uri' => $this->uriColumn,
		);
		config_append_assc('comment_module', $this->module, $config);
	}
	
	public function drop(){
		$config = cc('comment_module');
		unset($config[$this->module]);
		config_set('comment_module', $config);
	}
}
?>
