<?php
execute_add_class('forumentry', 'ForumEntry');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('ForumEntryModel.class.inc');
include('forum.tool.inc');

class ForumEntry extends Content{
	function ForumEntry(){
		$this->tableName = 'forumentry';
		$this->moduleName = 'forumentry';
		$this->moduleTitle = tt('Forum Entry');
		$this->init(new ForumEntryModel());
		document_set_path(tt('Forum'), 'forum');
	}
	
	public function index(){
		if($this->isSingleEntry()) return $this->renderSingleForumEntry();
		else return $this->renderMultipleForumEntrys();
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		$this->dataByID['content'] = $this->dataByID['intro'].$this->dataByID['content'];
		return render($this->dataByID, 'content_print.tpl', 'forumentry_print');
	}
	
	protected function getSummary(){
		return $this->dataByID['intro'];
	}
	
	private function renderSingleForumEntry(){
		$this->id = mid();
		$this->selectByID($this->column);
		if($this->isReadable()) return $this->executeRender();
		else $this->accessDeniedEntry();
	}
	
	private function renderMultipleForumEntrys(){
		head_add_css('forum.css');
		$column = $this->modelConnector->getColumnNameExcepted(array('content'));
		$this->selectFirstPage($column, cc('forum_entries_number'));
		$this->getCommentNumber();
		$this->getDataEditable();
		$this->setPathMutiplePage();
		$renderArray = array(
			'data' => $this->data,
			'show_category' => in_array('category_icon', cc('forum_appearance')),
		);
		$render = render($renderArray, 'multipleforums.tpl', 'multiple_forums');
		$render.= $this->pager->render('forum'.$this->getPageMode());
		return $render;
	}
	
	private function executeRender(){
		head_add_css('forum.css');
		$this->prepareRender();
		$render = render($this->dataByID, 'singleforum.tpl', 'single_forum');
		$render.= $this->comment->render();
		$this->setDocumentData();
		return $render;
	}
	
	private function prepareRender(){
		$this->handlePublishingStatus();
		$this->getSibling();
		$this->initComment();
		$this->insertTracker('read');
		$this->addMetaData();
		$this->getAppearanceConfiguration();
		$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
	}
	
	private function getSibling(){
		$publishTime = $this->dataByID['unformatted_publish_time'];
		$clause = 'WHERE (section='.SECTION." AND publish_time > '$publishTime' AND publishing_status < 2) ";
		$clause.= 'ORDER BY publish_time LIMIT 1';
		$next = db_select('forumentry', array('id', 'topic', 'uri'), $clause);
		$clause = 'WHERE (section='.SECTION." AND publish_time < '$publishTime' AND publishing_status < 2) ";
		$clause.= 'ORDER BY publish_time DESC LIMIT 1';
		$back = db_select('forumentry', array('id', 'topic', 'uri'), $clause);
		$this->dataByID['next'] = array_values($next);
		$this->dataByID['back'] = array_values($back);
	}
	
	private function getAppearanceConfiguration(){
		$appearance = cc('forum_appearance');
		if(!is_array($appearance)) $appearance = array();
		$this->dataByID['show_avatar'] = in_array('avatar', $appearance);
		$this->dataByID['show_category'] = in_array('category_icon', $appearance);
		$this->dataByID['show_sibling'] = in_array('sibling', $appearance);
	}
}
?>
