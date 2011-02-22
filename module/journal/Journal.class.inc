<?php
execute_add_class('journal', 'Journal');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('JournalModel.class.inc');

class Journal extends Content{
	function Journal(){
		$this->tableName = 'journal';
		$this->moduleName = 'journal';
		$this->moduleTitle = tt('Journal');
		$this->init(new JournalModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		if($this->isSingleEntry()) return $this->renderSingleJournal();
		else return $this->renderMultipleJournals();
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		$this->dataByID['content'] = $this->dataByID['intro'].$this->dataByID['content'];
		return render($this->dataByID, 'content_print.tpl', 'journal_print');
	}
	
	protected function getSummary(){
		return $this->dataByID['intro'];
	}
	
	private function renderSingleJournal(){
		$this->id = mid();
		$this->selectByID($this->column);
		if($this->isReadable()) return $this->executeRender();
		else $this->accessDeniedEntry();
	}
	
	private function renderMultipleJournals(){
		head_add_css('journal.css');
		$column = $this->modelConnector->getColumnNameExcepted(array('content'));
		$this->selectFirstPage($column, cc('journal_entries_number'));
		$this->getCommentNumber();
		$this->getDataEditable();
		$this->setPathMutiplePage();
		$this->translateData();
		$renderArray = array(
			'data' => $this->data,
			'show_category' => in_array('category_icon', cc('journal_appearance')),
		);
		$render = render($renderArray, 'multiplejournals.tpl', 'multiple_journals');
		$render.= $this->pager->render('journal'.$this->getPageMode());
		return $render;
	}
	
	private function executeRender(){
		head_add_css('journal.css');
		$this->prepareRender();
		$render = render($this->dataByID, 'singlejournal.tpl', 'single_journal');
		$render.= $this->comment->render();
		$this->setDocumentData();
		return $render;
	}
	
	private function prepareRender(){
		$this->translateDataByID();
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
		$next = db_select('journal', array('id', 'topic', 'uri'), $clause);
		$clause = 'WHERE (section='.SECTION." AND publish_time < '$publishTime' AND publishing_status < 2) ";
		$clause.= 'ORDER BY publish_time DESC LIMIT 1';
		$back = db_select('journal', array('id', 'topic', 'uri'), $clause);
		$this->dataByID['next'] = array_values($next);
		$this->dataByID['back'] = array_values($back);
	}
	
	private function getAppearanceConfiguration(){
		$appearance = cc('journal_appearance');
		if(!is_array($appearance)) $appearance = array();
		$this->dataByID['show_avatar'] = in_array('avatar', $appearance);
		$this->dataByID['show_category'] = in_array('category_icon', $appearance);
		$this->dataByID['show_sibling'] = in_array('sibling', $appearance);
	}
}
?>
