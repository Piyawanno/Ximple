<?php
execute_add_class('comment', 'Comment');
include('CommentModel.class.inc');

class Comment extends Control{
	private $mode;
	private $parent;
	private $permission;
	private $parentData;
	
	function Comment($mode=null, $parent=null, $permission=null, $parentWriter=null){
		$this->tableName = 'comment';
		$this->moduleName = 'comment';
		$this->moduleTitle = tt('Comment');
		$this->setMode($mode);
		$this->setParent($parent);
		$this->setPermission($permission);
		$this->setAccess();
		$this->init(new CommentModel($this->mode, $this->parent, $parentWriter));
	}
	
	public function render(){
		$render = $this->renderEntry();
		$render.= $this->write();
		return $render;
	}
	
	public function write(){
		if($this->isWritable()){
			$this->formMeta->id = $this->moduleName;
			$this->formMeta->title = cc($this->mode.'_comment_write_label');
			$this->formMeta->isCaptcha = true;
			$this->formMeta->mode = 'comment_insert/page/'.$this->pager->getNextPage();
			return $this->renderInsertForm(false);
		}else{
			return '';
		}
	}
	
	public function insert(){
		if($this->isWritable()){
			Control::insert();
			$column = array('id', 'topic', 'writer');
			$this->parentData = db_select($this->mode, $column, 'WHERE id='.$this->parent);
			$this->parentData = $this->parentData[$this->parent];
			$this->insertTracker();
			$this->insertNotify();
			db_update($this->mode, array('comment_time' => NOW), $this->parent);
			document_set_redirect($this->mode.'/'.$this->parent.'/page/'.pid().'#last_comment');
		}
	}
	
	public function update(){
		Control::update();
		document_set_redirect($this->mode.'/'.$this->parent.'/page/'.pid().'#comment_'.$this->id);
	}
	
	public function listPage(){
		$clause = 'WHERE (writer_id='.USER_ID.')';
		$label = tt('My Comments');
		$description = '';
		return $this->renderListPage($clause, $label, $description);
	}
	
	public function contributorListPage(){
		$clause = 'WHERE (parent_writer='.USER_ID.')';
		$label = tt('Comments on my Contributions');
		$description = '';
		return $this->renderListPage($clause, $label, $description);
	}
	
	public function sectionListPage(){
		$clause = 'WHERE (section='.SECTION.')';
		$label = sprintf(tt('Comments in %s'), cc('section_name'));
		$description = '';
		return $this->renderListPage($clause, $label, $description);
	}
	
	private function setAccess(){
		$this->ownerColumn = 'writer_id';
		if($this->isWritable()) $this->addAccessMethod('guest', 'insert');
		$this->setAdmin('comment_admin');
		$this->addAction('comment_list', 'listPage');
		$this->addAction('comment_section_list', 'sectionListPage');
		$this->addAction('comment_contributor_list', 'contributorListPage');
		$this->addAccessMethod('user', 'listPage');
		$this->addAccessMethod('user', 'sectionListPage');
		$this->addAccessMethod('user', 'contributorListPage');
	}
	
	protected function renderListPage($clause, $label, $description){
		$title = sprintf(tt('List of %s'), $label);
		document_set_path($title);
		document_set_title($title);
		$this->listMeta->title = $title;
		$this->listMeta->mode = $this->moduleName;
		$this->listMeta->defaultOrderDesc = 'id';
		$this->listMeta->description = $description;
		$this->selectListPage(20, $clause, array('mode'));
		$this->renderParentTopic();
		return Control::renderListPage();
	}
	
	private function setMode($mode){
		if($mode) $this->mode = $mode;
		elseif(pp('mode')) $this->mode = addslashes(pp('mode'));
		elseif(gg('module')) $this->mode = addslashes(gg('module'));
	}
	
	private function setParent($parent){
		if($parent) $this->parent = $parent;
		elseif(pp('parent')) $this->parent = (int) pp('parent');
		elseif(gg('parent')) $this->parent = (int) gg('parent');
	}
	
	private function setPermission($permission){
		if($permission){
			$this->permission = $permission;
		}elseif(!empty($this->mode) and !empty($this->mode)){
			$clause = 'WHERE id='.((int) $this->parent);
			$permission = db_select_single_column($this->mode, 'comment_permission', $clause, false);
			$this->permission = $permission[0];
		}
	}
	
	
	private function renderEntry(){
		if($this->isReadable()){
			head_add_css('module/comment/theme/comment.css');
			$clause = 'WHERE parent='.$this->parent." AND mode='".$this->mode."' ORDER BY id";
			$this->selectPage($this->column, cc($this->mode.'_comment_page_length'), $clause);
			$this->checkDataEditable();
			$this->setGuestName();
			$this->checkNew();
			$pager = $this->pager->render(mm().'/'.mid());
			$render = $pager;
			$renderArray = array(
				'data' => $this->data,
				'is_avatar' => cc($this->mode.'_comment_show_avatar'),
			);
			$render.= render($renderArray, 'module/comment/theme/comment.tpl', 'comment');
			$render.= $pager;
			return $render;
		}else{
			return '';
		}
	}
	
	private function isReadable(){
		return ($this->permission < 3);
	}
	
	private function isWritable(){
		if($this->permission == 0) return true;
		elseif($this->permission == 0 and !authority_is_guest()) return true;
		else return false;
	}
	
	private function checkDataEditable(){
		foreach($this->data as $key => $value){
			$this->data[$key]['editable'] = authority_owner('comment_admin', $value['writer_id']);
		}
	}
	
	private function setGuestName(){
		foreach($this->data as $key => $value){
			if($value['writer_id']['id'] == -1){
				$this->data[$key]['writer_id']['login_name'] = $value['writer'];
			}
		}
	}
	
	private function checkNew(){
		if(!authority_is_guest()){
			$idArray = array_keys($this->data);
			$count = count_get_array('comment'.USER_ID, $idArray);
			foreach($count as $id => $number){
				$this->data[$id]['is_new'] = ($number == 0);
			}
			count_increase('comment'.USER_ID, $idArray);
		}else{
			foreach($this->data as $key => $value){
				$this->data[$key]['is_new'] = false;
			}
		}
	}
	
	private function insertTracker(){
		if(!authority_is_guest()){
			include_once(ROOT_PATH.'module/tracker/tracker.tool.inc');
			$writerName = db_select_single_column('users', 'login_name', 'WHERE id='.$this->parentData['writer'], false);
			$trackerData = array(
				'mode' => $this->mode,
				'id' => $this->parent,
				'topic' => $this->parentData['topic'],
				'writer' => $this->parentData['writer'],
				'writer_name' => $writerName[0],
				'action' => 'comment',
			);
			tracker_insert($trackerData);
		}
	}
	
	private function insertNotify(){
		$p = tt('%s commented on <a href="%s">%s</a>.');
		$uri = SECTION_URI.Q.$this->mode.'/'.$this->parent.'/page/'.pid().'#last_comment';
		$message = sprintf($p, pp('writer'), $uri, $this->parentData['topic']);
		if($this->parentData['writer'] != USER_ID){
			notify_add_info($message, $this->parentData['writer']);
		}
		$clause = "WHERE mode='".$this->mode."' AND parent=".$this->parent." AND writer_id != -1 GROUP BY writer_id";
		$relatedUser = db_select_single_column('comment', 'writer_id', $clause, false);
		foreach($relatedUser as $uid){
			if($uid != $this->parentData['writer'] and $uid != USER_ID){
				notify_add_info($message, $uid);
			}
		}
	}
	
	private function renderParentTopic(){
		$mode = array();
		foreach($this->data as $key => $value){
			$mode[$value['mode']][] = $value['parent'];
		}
		
		$parent = array();
		foreach($mode as $table => $id_array){
			$clause = 'WHERE id='.join(' OR id=', $id_array);
			$parent[$table] = db_select($table, array('id', 'topic', 'uri'), $clause);
		}
		
		foreach($this->data as $key => $value){
			$uri = render_uri($value['mode'], $parent[$value['mode']][$value['parent']]);
			$topic = $parent[$value['mode']][$value['parent']]['topic'];
			$this->data[$key]['parent'] = '<a href="'.$uri.'">'.$topic.'</a>';
		}
	}
}

?>
