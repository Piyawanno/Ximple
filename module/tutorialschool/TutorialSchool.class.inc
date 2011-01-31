<?php
execute_add_class('tutorialschool', 'TutorialSchool');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('TutorialSchoolModel.class.inc');

class TutorialSchool extends Content{
	function TutorialSchool(){
		$this->tableName = 'tutorialschool';
		$this->moduleName = 'tutorialschool';
		$this->moduleTitle = tt('TutorialSchool');
		$this->init(new TutorialSchoolModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		if($this->isSingleEntry()) return $this->renderSingleTutorialSchool();
		else return $this->renderMultipleTutorialSchools();
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		$this->dataByID['content'] = $this->dataByID['intro'].$this->dataByID['content'];
		return render($this->dataByID, 'content_print.tpl', 'tutorialschool_print');
	}
	
	protected function getSummary(){
		return $this->dataByID['intro'];
	}
	
	private function renderSingleTutorialSchool(){
		$this->id = mid();
		$this->selectByID($this->column);
		if($this->isReadable()) return $this->executeRender();
		else $this->accessDeniedEntry();
	}
	
	private function renderMultipleTutorialSchools(){
		head_add_css('tutorialschool.css');
		$column = $this->modelConnector->getColumnNameExcepted(array('content'));
		$this->selectFirstPage($column, cc('tutorialschool_entries_number'));
		$this->getCommentNumber();
		$this->getDataEditable();
		$this->setPathMutiplePage();
		$this->translateData();
		$renderArray = array(
			'data' => $this->data,
			'show_category' => in_array('category_icon', cc('tutorialschool_appearance')),
		);
		$render = render($renderArray, 'multipletutorialschools.tpl', 'multiple_tutorialschools');
		$render.= $this->pager->render('tutorialschool'.$this->getPageMode());
		return $render;
	}
	
	private function executeRender(){
		head_add_css('tutorialschool.css');
		$this->prepareRender();
		$render = render($this->dataByID, 'singletutorialschool.tpl', 'single_tutorialschool');
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
		$next = db_select('tutorialschool', array('id', 'topic', 'uri'), $clause);
		$clause = 'WHERE (section='.SECTION." AND publish_time < '$publishTime' AND publishing_status < 2) ";
		$clause.= 'ORDER BY publish_time DESC LIMIT 1';
		$back = db_select('tutorialschool', array('id', 'topic', 'uri'), $clause);
		$this->dataByID['next'] = array_values($next);
		$this->dataByID['back'] = array_values($back);
	}
	
	private function getAppearanceConfiguration(){
		$appearance = cc('tutorialschool_appearance');
		if(!is_array($appearance)) $appearance = array();
		$this->dataByID['show_avatar'] = in_array('avatar', $appearance);
		$this->dataByID['show_category'] = in_array('category_icon', $appearance);
		$this->dataByID['show_sibling'] = in_array('sibling', $appearance);
	}
}
?>
