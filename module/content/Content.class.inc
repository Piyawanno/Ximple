<?php
include_once('content.tool.inc');
include('ContentModel.class.inc');

abstract class Content extends Control{
	protected $comment;
	
	public function write(){
		$this->setConfigForm();
		$this->writeLabel = sprintf(tt('Write new %s entry'), $this->moduleTitle);
		return Control::write();
	}
	
	public function edit(){
		$this->setConfigForm();
		return Control::edit();
	}
	
	public function insert(){
		Control::insert();
		$this->selectByID($this->column, true);
		$this->updateFreeTag();
		$this->insertTracker('write');
		if($this->isReadable(false)){
			$feedData = $this->formatFeedData();
			feed_insert($this->moduleName, $feedData);
		}
		document_set_redirect($this->moduleName.'/'.$this->id);
	}
	
	public function update(){
		Control::update();
		$this->updateFreeTag();
		$this->insertTracker('update');
		if($this->isReadable(false)){
			$feedData = $this->formatFeedData();
			feed_update($this->moduleName, $feedData);
		}
		document_set_redirect($this->moduleName.'/'.$this->id);
	}
	
	public function drop(){
		include_once(ROOT_PATH.'module/feed/feed.tool.inc');
		$this->updateFreeTag();
		$this->insertTracker('drop');
		feed_drop($this->moduleName, $this->id);
		db_drop_many('comment', 'parent='.$this->id);
		Control::drop();
	}
	
	public function listPage(){
		$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND publish_time <= '.date('Y-m-d').')';
		$title = sprintf(tt('List of %s entries'), $this->moduleTitle);
		document_set_path($title);
		document_set_title($title);
		$this->listMeta->mode = $this->moduleName.'_list';
		return $this->renderListPage($clause);
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		return render($this->dataByID, 'content_print.tpl', $this->moduleName.'_print');
	}
	
	public function contributorListPage(){
		$title = sprintf(tt('List of %s entries for Contributor'), $this->moduleTitle);
		document_set_path($title);
		document_set_title($title);
		$p = tt('You as Editor can use this page to access the entries of %s in Section.');
		$this->listMeta->description = sprintf($p, $this->moduleTitle);
		$this->listMeta->mode = $this->moduleName.'_contributor_list';
		return $this->renderListPage('WHERE (writer='.USER_ID.')');
	}
	
	public function editorListPage(){
		$this->modelConnector->setAttribute('writer', 'isList', true);
		$title = sprintf(tt('List of %s entries for Editor'), $this->moduleTitle);
		document_set_path($title);
		document_set_title($title);
		$p = tt('In the following list, your own entries of %s are shown. You can use this page to access them.');
		$this->listMeta->description = sprintf($p, $this->moduleTitle);
		$this->listMeta->mode = $this->moduleName.'_editor_list';
		return $this->renderListPage('WHERE (section='.SECTION.')');
	}
	
	public function initModule($requirement){
		Control::initModule($requirement);
		content_init_module($this->moduleName, $this->moduleTitle);
	}
	
	public function dropModule(){
		Control::dropModule();
		include_once('content.tool.inc');
		content_drop_module($this->moduleName, $this->moduleTitle);
	}
	
	protected function init($modelObj, $isEmbed=false, $setPath=true){
		Control::init($modelObj, $isEmbed, $setPath);
		$this->setAccess();
	}
	
	protected function renderListPage($clause){
		$this->listMeta->title = sprintf(tt('List of %s entries'), $this->moduleTitle);
		$this->listMeta->defaultOrderDesc = 'id';
		$this->selectListPage(20, $clause);
		$this->renderWriter();
		$this->setListWriteIcon();
		$this->setListEditIcon();
		$this->setListDropIcon();
		return Control::renderListPage();
	}
	
	protected function selectFirstPage($column, $pageLength, $arg=array()){
		if(gg('tag') or isset($arg['tag'])){
			$this->selectFirstPageTag($column, $pageLength, $arg);
		}elseif(gg('year') or isset($arg['year'])){
			$this->selectFirstPageArchive($column, $pageLength, $arg);
		}elseif(MODE_PAGE == 0 or (isset($arg['page']) and $arg['page'] == 0)){
			$this->selectFirstPageFearured($column, $pageLength);
		}else{
			$this->selectFirstPageCommon($column, $pageLength);
		}
	}
	
	protected function postSelect(){
		Control::postSelect();
		$this->addCategoryToFreeTag();
		$this->clearDailyCache();
	}
	
	protected function getCommentNumber(){
		$idArray = array_keys($this->data);
		if(count($idArray)){
			$clause = 'WHERE (parent='.join(' OR parent=', $idArray).") AND mode='".$this->moduleName."'GROUP BY parent";
			$commentNumber = db_select('comment', array('parent', 'COUNT(id) as number'), $clause);
			foreach($commentNumber as $key=>$value){
				$this->data[$value['parent']]['comment_no'] = $value['number'];
			}
		}
	}
	
	protected function getDataEditable(){
		foreach($this->data as $key => $value){
			if(isset($value['writer'])){
				$this->data[$key]['editable'] = $this->isEditable($value['writer']['id']);
			}else{
				break;
			}
		}
	}
	
	protected function isReadable($checkEdit=true){
		$publishTime = strtotime($this->dataByID['publish_time']);
		if(strlen($this->dataByID['publishing_status']) > 1){
			$publishingMap = array_flip(content_get_publishing_status());
			$publishingStatus = $publishingMap[$this->dataByID['publishing_status']];
		}else{
			$publishingStatus = $this->dataByID['publishing_status'];
		}
		if($publishingStatus < 2 and $publishTime <= time()) return true;
		elseif($checkEdit and $this->isEditable($this->dataByID['writer']['id'])) return true;
		else return false;
	}
	
	protected function isEditable($writerID){
		if(authority_group($this->moduleName.'_admin')) return true;
		if(authority_group($this->moduleName.'_editor')) return true;
		if(authority_owner($this->moduleName.'_contributor', $writerID)) return true;
		return false;
	}
	
	protected function getPageMode(){
		if(gg('tag')) return '/tag/'.gg('tag');
		if(gg('year')) return '/year/'.gg('year').'/month/'.gg('month').'/day/'.gg('day');
	}
	
	protected function setPathMutiplePage(){
		if(strlen(gg('tag'))){
			document_set_path(gg('tag'), $this->moduleName.'/tag/'.gg('tag'));
		}elseif(strlen(gg('year'))){
			$archievTime = date('F Y', strtotime('01-'.gg('month').'-20'.gg('year')));
			document_set_path(tt('Archieve'), $this->moduleName.'_archiev');
			document_set_path($archievTime, $this->moduleName.'/year/'.gg('year').'/month/'.gg('month'));
		}
	}
	
	protected function initComment(){
		if(!$this->comment){
			include_once(ROOT_PATH.'module/comment/Comment.class.inc');
			if(!isset($this->dataByID['comment_permission'])) $permission = null;
			else $permission = $this->dataByID['comment_permission'];
			$this->comment = new Comment($this->moduleName, $this->id, $permission, $this->dataByID['writer']['id']);
		}
	}
	
	protected function getSummary(){
		mb_internal_encoding('utf8');
		return mb_substr(strip_tags($this->dataByID['content']), 0, 2000);
	}
	
	protected function insertTracker($action){
		if(!authority_is_guest()){
			include_once(ROOT_PATH.'module/tracker/tracker.tool.inc');
			$data = $this->dataByID;
			if(!is_array($this->dataByID['writer'])){
				$clause = 'WHERE id='.$this->dataByID['writer'];
				$writerName = db_select_single_column('users', 'login_name', $clause, false);
				$this->dataByID['writer_name'] = $writerName[0];
				$data['writer'] = $this->dataByID['writer'];
				$data['writer_name'] = $writerName[0];
			}else{
				$data['writer'] = $this->dataByID['writer']['id'];
				$data['writer_name'] = $this->dataByID['writer']['login_name'];
			}
			$data['action'] = $action;
			$data['mode'] = $this->moduleName;
			tracker_insert($data);
		}
	}
	
	protected function setConfigForm(){
		$tags = $this->getNewConfigForm(tt('category & tags'));
		$tags->append('category');
		$tags->append('freetag');
		
		$publish = $this->getNewConfigForm(tt('publishing and comment'));
		$publish->append('publishing_status');
		$publish->append('publish_time');
		$publish->append('comment_permission');
		
		$searchEngine = $this->getNewConfigForm(tt('search engine'));
		$searchEngine->append('uri');
		$searchEngine->append('description');
		
		if(uu('editor') == 1 or uu('editor') == 2){
			$code = $this->getNewConfigForm(tt('code writer'));
			$code->append('code');
		}
	}
	
	protected function addMetaData(){
		document_add_keywords($this->dataByID['freetag']);
		document_set_description($this->dataByID['description']);
	}
	
	protected function formatFeedData(){
		include_once(ROOT_PATH.'module/feed/feed.tool.inc');
		$category = db_select_single_column('category', 'category', 'WHERE id='.$this->dataByID['category'], false);
		$this->getCommentNumber();
		$data = $this->data[$this->id];
		$data['writer'] = $this->dataByID['writer_name'];
		$data['summary'] = $this->getSummary();
		$data['freetag'].= ', '.$category[0];
		return $data;
	}
	
	private function selectFirstPageTag($column, $pageLength, $arg){
		if(isset($arg['tag'])) $tag = $arg['tag'];
		else $tag = gg('tag');
		$tag = addslashes($tag);
		$tagClause = $this->getTagClause($tag);
		$categoryClause = $this->getCategoryClause($tag);
		
		if(strlen($tagClause)){
			if(strlen($categoryClause)==0) $tagClause = "AND ($tagClause)";
			else $tagClause = "AND ($tagClause OR $categoryClause)";
		}else{
			if(strlen($categoryClause)==0) $tagClause = "AND id=0";
			else $tagClause = "AND ".$categoryClause;
		}

		$clause  = "WHERE (section=".SECTION." AND publishing_status < 2 ";
		$clause .= "AND publish_time <= '".date('Y-m-d')."' $tagClause )";
		$clause .= "ORDER BY publish_time DESC";
		$this->selectPage($column, $pageLength, $clause);
	}
	
	private function selectFirstPageArchive($column, $pageLength, $arg){
		if(isset($arg['year'])) $year = (int) $arg['year'];
		else $year = (int) gg('year');
		
		if(isset($arg['month'])) $month = (int) $arg['month'];
		else $month = (int) gg('month');
		
		if(isset($arg['day'])) $day = (int) $arg['day'];
		else $day = (int) gg('day');
		
		$publishDate = "AND publish_time <= '".date('Y-m-d')."'";
		if(empty($day)){
			$archive  = " (publish_time > '$year-$mounth-1' AND publish_time < '$year-$mounth--31' $publishDate)";
		}else{
			$date = "$year-$mounth-$day";
			$archive  = " (publish_time >= '$data 00:00:00' AND publish_time < '$date 23:59:59' $publishDate)";
		}
		$clause = "WHERE ($archive AND section=".SECTION." AND publishing_status < 2)";
		$clause.= "ORDER BY publish_time DESC";
		$this->selectPage($column, $pageLength, $clause);
	}
	
	private function selectFirstPageFearured($column, $pageLength){
		$clause = "WHERE (section=".SECTION." AND publishing_status=1 AND publish_time <= '".date('Y-m-d')."') ";
		$clause.= "ORDER BY publish_time DESC";
		$this->selectPage($column, $pageLength, $clause);
		$featuredData = $this->data;
		
		$this->selectFirstPageCommon($column, $pageLength);
		foreach($featuredData as $key => $value){
			$this->data[$key] = $value;
		}
	}
	
	private function selectFirstPageCommon($column, $pageLength){
		$clause = "WHERE (section=".SECTION." AND publishing_status=0 AND publish_time <= '".date('Y-m-d')."') ";
		$clause.= "ORDER BY publish_time DESC";
		$this->selectPage($column, $pageLength, $clause);
	}
	
	private function setAccess(){
		$adminGroup = $this->moduleName.'_admin';
		$editorGroup = $this->moduleName.'_editor';
		$contributorGroup = $this->moduleName.'_contributor';
		$this->addAction($this->moduleName.'_list', 'listPage');
		$this->addAction($this->moduleName.'_editor_list', 'editorListPage');
		$this->addAction($this->moduleName.'_contributor_list', 'contributorListPage');
		
		$this->ownerColumn = 'writer';
		$this->setAdmin($adminGroup);
		
		$this->addAccessMethod($editorGroup, 'write');
		$this->addAccessMethod($editorGroup, 'edit');
		$this->addAccessMethod($editorGroup, 'insert');
		$this->addAccessMethod($editorGroup, 'update');
		$this->addAccessMethod($editorGroup, 'drop');
		$this->addAccessMethod($editorGroup, 'editorListPage');
		
		$this->addAccessMethod($contributorGroup, 'write');
		$this->addAccessMethod($contributorGroup, 'insert');
		$this->addAccessMethod($contributorGroup, 'contributorListPage');
		
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'listPage');
		$this->addAccessMethod('guest', 'printPage');
	}
	
	
	private function renderWriter(){
		foreach($this->data as $key => $value){
			if(isset($value['writer'])){
				$this->data[$key]['writer'] = render_profile_link($value['writer']);
			}else{
				break;
			}
		}
	}
	
	private function updateFreeTag(){
		include_once(ROOT_PATH.'module/freetag/freetag.tool.inc');
		freetag_update(pp('freetag'), $this->moduleName, $this->id);
	}
	
	private function addCategoryToFreeTag(){
		foreach($this->data as $key => $value){
			if(isset($value['category']) and isset($value['freetag'])){
				$category = $value['category']['category'];
				$this->data[$key]['freetag'] = array_merge(array($category), $value['freetag']);
			}else{
				break;
			}
		}
		if(!empty($this->dataByID)) $this->dataByID = $this->data[$this->id];
	}
	
	private function clearDailyCache(){
		$dateFile = ROOT_PATH.'files/dbcache/'.$this->moduleName.'/lastclear.txt';
		$setClearDate = true;
		if(is_file($dateFile)){
			if(io_read_file($dateFile) == date('Y-m-d')) $setClearDate = false;
			else io_clear_directory(ROOT_PATH.'files/dbcache/'.$this->moduleName);
		}
		if($setClearDate) io_write_file($dateFile, date('Y-m-d'));
	}
	
	private function getTagClause($tag){
		$clause = "WHERE (freetag='".$tag."' AND mode='".$this->moduleName."')";
		$tagData = db_select('freetag', array('content_id'), $clause);
		$contentID = array();
		foreach($tagData as $key => $value){
			$contentID[] = $value['content_id'];
		}
		if(count($tagData)) return 'id='.join(' OR id=', $contentID);
		else return '';
	}
	
	private function getCategoryClause($tag){
		$clause = "WHERE (category='".$tag."' AND mode='".$this->moduleName."')";
		$category = array_keys(db_select_single_column('category', 'id', $clause));
		if(isset($category[0])) return 'category='.$category[0];
		else return '';
	}
	
}

?>
