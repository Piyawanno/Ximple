<?php
execute_add_class('meeting', 'Meeting');
include_once(MODULE_PATH.'content/Content.class.inc');
include_once('MeetingModel.class.inc');

class Meeting extends Content{
	function Meeting(){
		$this->tableName = 'meeting';
		$this->moduleName = 'meeting';
		$this->moduleTitle = tt('Meeting');
		$this->setAccess();
		$this->init(new MeetingModel());
		$participant = $this->getNewConfigForm(tt('participant groups'));
		$participant->append('paricipant_group');
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		if($this->isSingleEntry()) return $this->renderSingleMeeting();
		else return $this->renderCalendar();
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		$this->dataByID['content'] = $this->dataByID['intro'].$this->dataByID['content'];
		return render($this->dataByID, 'content_print.tpl', 'meeting_print');
	}
	
	public function participate(){
	
	}
	
	public function participatePerMail(){
	
	}
	
	private function renderSingleMeeting(){
		$this->id = mid();
		$this->selectByID($this->column);
		$this->publishDate = date('Y-m-d H:i:s', strtotime($this->dataByID['publish_time']));
		if($this->isReadable()) return $this->executeRender();
		else $this->accessDeniedEntry();
	}
	
	private function renderCalendar(){
		head_add_css('meeting.css');
		document_set_path(tt('Meeting Calendar'));
		list($month, $year) = input_get_month();
		$this->getMeetingInMonth($month, $year);
		$calendarData = $this->getCalendarData($month);
		$calendar = render_calendar($calendarData, 'meeting', $month, $year);
		$renderArray = array(
			'calendar' => $calendar,
			'month' => date('F Y', strtotime("$year-$month-01")),
			'write_icon' => $this->renderWriteIcon(),
			'data' => $this->data,
		);
		return render($renderArray, 'meeting_calendar.tpl', 'meeting_calendar');
	}
	
	private function getMeetingInMonth($month, $year){
		if(strlen($month) == 1) $month = '0'.$month;
		$date = "'$year-$month-01 00:00:00'";
		$clause  = "WHERE (meeting_date >= $date AND meeting_date <= $date) ";
		$clause .= "AND publishing_status < 2";
		$this->select(array('id', 'topic', 'meeting_date', 'meeting_period'), $clause);
	}
	
	private function getCalendarData($month){
		$this->getDayOfMonth($month);
		$calendarArray = array();
		for($i=1; $i<=31; $i++){
			foreach($this->data as $key => $value){
				if($i == $value['day']){
					$calendarArray[$i]['class'] = 'active_meeting';
					$calendarArray[$i]['link'][] = 'meeting/'.$key;
				}
			}
		}
		return $calendarArray;
	}
	
	private function getDayOfMonth($month){
		foreach($this->data as $key => $value){
			$this->data[$key] = $this->processMeetingTime($value);
		}
	}
	
	private function processDayOfMonth($date, $month){
		$time = strtotime($date);
		$dateMonth = (int) date('n', $time);
		if($dateMonth < $month) return -1;
		elseif($dateMonth > $month) return 1000;
		else return (int) date('j', $time);
	}
	
	private function executeRender(){
		head_add_css('meeting.css');
		$this->prepareRender();
		$render = $this->renderWriteIcon();
		$render.= render($this->dataByID, 'meeting.tpl', 'meeting');
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
		$this->dataByID = $this->processMeetingTime($this->dataByID);
	}
	
	private function processMeetingTime($data){
		$meetingTime = strtotime($data['meeting_date']);
		$data['meeting_date'] = date(cc('time_format'), $meetingTime);
		$data['meeting_time'] = date('H:i', $meetingTime);
		$data['end_time'] = date('H:i', $meetingTime + $data['meeting_period']);
		$data['meeting_period'] = date('H:i', $data['meeting_period']);
		$data['day'] = (int) date('j', $meetingTime);
		return $data;
	}
	
	private function getAppearanceConfiguration(){
		$appearance = cc('meeting_appearance');
		if(!is_array($appearance)) $appearance = array();
		$this->dataByID['show_avatar'] = in_array('avatar', $appearance);
		$this->dataByID['show_category'] = in_array('category_icon', $appearance);
	}
	
	private function renderWriteIcon(){
		if($this->isCallable('write')){
			return render_write_icon('meeting_write', tt('Write new Meeting entry'));
		}
	}
	
	private function isParticipant(){
	
	}
	
	private function setAccess(){
		$this->addAction('meeting_participate', 'participate');
		$this->addAction('meeting_participate_per_mail', 'participatePerMail');
		
		$this->addAccessMethod('user', 'participate');
		$this->addAccessMethod('guest', 'participatePerMail');
	}
}
?>
