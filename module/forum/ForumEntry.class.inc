<?php
if(execute_get_class('forum') == null)  execute_add_class('forum', 'ForumEntry');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include_once('forum.tool.inc');
include('ForumEntryModel.class.inc');

class ForumEntry extends Content{
	function ForumEntry(){
		$this->tableName = 'forum_entry';
		$this->moduleName = 'forum_entry';
		$this->moduleTitle = tt('Forum Entry');
		$this->addAction('forum_entry_insert_comment', 'insertComment');
		$this->addAccessMethod('guest', 'insertComment');
		$this->init(new ForumEntryModel());
		$this->writeLabel = tt('Write new Forum Entry');
		document_set_path(tt('Forum'), 'forum');
		menu_activate('forum');
	}
	
	public function index(){
		$this->id = gg('id');
		$this->selectByID($this->column);
		
		count_increase($this->moduleName, $this->id);
		if(!authority_is_guest()){
			count_increase('forum_entry'.USER_ID, $this->id);
		}
		head_add_css('forum.css');
		forum_set_path($this->dataByID['forum']);
		document_set_path($this->dataByID['topic']);
		
		$writerID = $this->dataByID['writer']['id'];
		$this->dataByID['show_avatar'] = true;
		$this->dataByID['editable'] = $this->isEditable($writerID);
		
		$this->initComment();
		$this->insertTracker('read');
		$this->comment->setTemplate('forumcomment.tpl');
		$this->comment->setInsertMode('forum_entry_insert_comment');
		
		$render = render($this->dataByID, 'forumentry.tpl', 'forumentry');
		$render.= $this->comment->render();
		
		return $render;
	}
	
	public function write(){
		$this->prepareForum();
		return Content::write();
	}
	
	public function insert(){
		Control::insert();
		$this->selectByID($this->column);
		$this->dataByID['category'] = forum_get_category_id($this->id);
		$this->insertTracker('write');
		if($this->isFeed() and $this->isReadable(false)){
			$feedData = $this->formatFeedData();
			feed_insert($this->moduleName, $feedData);
		}
		document_set_redirect('forum_entry/'.$this->id);
		count_increase('forum_entry_no', $this->dataByID['forum']);
	}
	
	public function insertComment(){
		$this->initComment();
		$this->comment->insert();
		$data = array(
			'last_commentator' => pp('writer'),
			'last_commentator_id' => USER_ID,
		);
		db_update('forum_entry', $data, pp('parent'));
		$this->id = pp('parent');
		$this->selectByID($this->column);
		count_increase('forum_comment_no', $this->dataByID['forum']);
	}
	
	public function edit(){
		$this->prepareForum();
		return Content::edit();
	}
	
	public function listPage(){
		$this->prepareForum();
		head_add_css('list.css');
		$renderArray = array(
			'data' => $this->getListData(),
			'forum' => forum_get_info(gg('forum')),
			'pager' => $this->pager->render('forum_entry_list/forum/'.gg('forum')),
		);
		return render($renderArray, 'forumlist.tpl', 'forumlist');
	}
	
	protected function setConfigForm(){
		$publish = $this->getNewConfigForm(tt('publishing and comment'));
		$publish->append('publishing_status');
		$publish->append('comment_permission');
	}
	
	protected function postSelect(){
		Control::postSelect();
		foreach($this->data as $key => $value){
			$this->data[$key]['uri'] = 	$value['topic'];
			if($value['writer']['id'] == -1){
				$this->data[$key]['writer']['login_name'] = $value['writer_name'];
			}
		}
	}
	
	protected function isReadable(){
		if($this->dataByID['publishing_status'] < 2) return true;
		elseif($this->isEditable($this->dataByID['writer']['id'])) return true;
		else return false;
	}
	
	protected function formatFeedData(){
		include_once(ROOT_PATH.'module/feed/feed.tool.inc');
		$this->getCommentNumber();
		$data = $this->data[$this->id];
		$data['writer']  = $this->dataByID['writer_name'];
		$data['summary'] = $this->dataByID['content'];
		$forum = forum_get_info($this->dataByID['forum']);
		$data['freetag'] = $forum['name'];
		return $data;
	}
	
	private function prepareForum(){
		$forumID = gg('forum');
		if($forumID){
			$allowedForums = forum_get_allowed_id();
			if(!in_array($forumID, $allowedForums)){
				error_denied();
			}
			forum_set_path($forumID);
		}
	}
	
	private function getListData(){
		$featuredData = $this->getListDataFromDB(1);
		$regularData = $this->getListDataFromDB(0);
		$data = array();
		foreach($featuredData as $key => $value){
			$value['icon'] = 'stick';
			$data[] = $value;
		}
		$regularData = $this->checkNew($regularData);
		foreach($regularData as $key => $value){
			$data[$key] = $this->getIcon($value);
			$data[$key] = $this->getCommentator($data[$key]);
		}
		return $data;
	}
	
	private function isCommentable($permission){
		if($permission == 0) return true;
		elseif($permission == 1 and !authority_is_guest()) return true;
		else return false;
	}
	
	private function checkNew($data){
		$count = count_get_array('forum_entry'.USER_ID, array_keys($data));
		foreach($count as $id => $number){
			$data[$id]['is_new'] = ($number == 0);
		}
		return $data;
	}
	
	private function getListDataFromDB($status){
		$forumID = (int) gg('forum');
		$column = array(
			'id',
			'topic',
			'write_time',
			'writer',
			'last_commentator',
			'last_commentator_id',
			'comment_time',
			'comment_permission'
		);
		$pattern = "WHERE forum=%d AND publishing_status=%d ORDER by comment_time DESC";
		$this->selectPage($column, 20, sprintf($pattern, $forumID, $status));
		$this->getCommentNumber();
		return $this->data;
	}
	
	private function getIcon($entry){
		if(isset($entry['comment_no'])){
			if($entry['comment_no'] > 25) $entry['icon'] = 'veryhot';
			elseif($entry['comment_no'] > 15) $entry['icon'] = 'hot';
			else $entry['icon'] = 'default';
		}elseif(!$this->isCommentable($entry['comment_permission'])){
			$entry['icon'] = 'lock';
		}elseif($entry['is_new']){
			$entry['icon'] = 'new';
		}else{
			$entry['icon'] = 'default';
		}
		return $entry;
	}
	
	private function getCommentator($entry){	
		if(strlen($entry['last_commentator']) and $entry['last_commentator_id']['id'] != -1){
			$entry['last_commentator'] = render_profile_link($entry['last_commentator_id']);
		}
		return $entry;
	}
}
?>
