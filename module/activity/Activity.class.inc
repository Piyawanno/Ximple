<?php
execute_add_class('activity', 'Activity');
include_once(MODULE_PATH.'content/Content.class.inc');
include_once('ActivityModel.class.inc');

class Activity extends Content{
	function Activity(){
		$this->tableName = 'activity';
		$this->moduleName = 'activity';
		$this->moduleTitle = tt('Activity');
		$this->addAction('activity_promote_widget', 'renderPromoteWidget');
		$this->addAccessMethod('guest', 'renderPromoteWidget');
		$this->init(new ActivityModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		if($this->isSingleEntry()) return $this->renderSingleActivity();
		else return $this->renderCalendar();
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		$this->dataByID['content'] = $this->dataByID['intro'].$this->dataByID['content'];
		return render($this->dataByID, 'content_print.tpl', 'activity_print');
	}
	
	protected function getSummary(){
		return $this->dataByID['content'];
	}
	
	protected function isReadable(){
		$status = $this->dataByID['publishing_status'];
		$promote = activity_get_publishing_status();
		return (Content::isReadable() or ($status == $promote[4]));
	}
	
	private function renderSingleActivity(){
		$this->id = mid();
		$this->selectByID($this->column);
		$this->publishDate = date('Y-m-d H:i:s', strtotime($this->dataByID['publish_time']));
		if($this->isReadable()) return $this->executeRender();
		else $this->accessDeniedEntry();
	}
	
	private function renderCalendar(){
		$month = (int) gg('month');
		$year = (int) gg('year');
		
		if(empty($month)) $month = date('n');
		if(empty($year)) $year = date('Y');
		
		return render_calendar(array(), 'activity', $month, $year);
	}
	
	private function executeRender(){
		head_add_css('activity.css');
		$this->prepareRender();
		$render = $this->renderWriteIcon();
		$render.= render($this->dataByID, 'activity.tpl', 'activity');
		$render.= $this->comment->render();
		$this->setDocumentData();
		return $render;
	}
	
	private function prepareRender(){
		$this->translateDataByID();
		$this->handlePublishingStatus();
		$this->initComment();
		$this->insertTracker('read');
		$this->addMetaData();
		$this->getAppearanceConfiguration();
		$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
	}
	
	private function getAppearanceConfiguration(){
		$appearance = cc('activity_appearance');
		if(!is_array($appearance)) $appearance = array();
		$this->dataByID['show_avatar'] = in_array('avatar', $appearance);
		$this->dataByID['show_category'] = in_array('category_icon', $appearance);
	}
	
	private function renderWriteIcon(){
		if($this->isCallable('write')){
			return render_write_icon('activity_write', tt('Write new Activity entry'));
		}
	}
}
?>
