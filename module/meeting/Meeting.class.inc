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
	
	public function edit(){
		if($this->isSummarizable($this->dataByID)){
			$this->modelConnector->setAttribute('summary', 'isForm', true);
		}
		return Content::edit();
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		$this->dataByID['content'] = $this->dataByID['content'].$this->dataByID['summary'];
		return render($this->dataByID, 'content_print.tpl', 'meeting_print');
	}
	
	public function participate(){
	
	}
	
	public function decline(){
	
	}
	
	public function participatePerMail(){
	
	}
	
	public function declinePerMail(){
	
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
		$monthBegin = "'$year-$month-01 00:00:00'";
		$monthEnd = "'$year-$month-".date('t', strtotime($monthBegin))." 23:59:59'";
		$clause  = "WHERE (meeting_date >= $monthBegin AND meeting_date <= $monthEnd) ";
		$clause .= "AND publishing_status < 2 ORDER BY meeting_date";
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
		$this->dataByID['participate_icon'] = $this->renderParticipateIcon();
		$this->dataByID['decline_icon'] = $this->renderDeclineIcon();
		$this->dataByID['participant'] = $this->getParticipant();
		$this->dataByID['disclaimer'] = $this->getDisclaimer();
		$this->dataByID['is_summarizable'] = $this->isSummarizable($this->dataByID);
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
	
	private function renderParticipateIcon(){
		if($this->isParticipant($this->dataByID)){
			$icon = 'module/meeting/theme/participate.png';
			return render_icon('meeting_participate', $icon, tt('join Meeting'));
		}
	}
	
	private function renderDeclineIcon(){
		if($this->isParticipant($this->dataByID)){
			$icon = 'files/icon/drop.png';
			return render_icon('meeting_decline', $icon, tt('decline Meeting'));
		}
	}
	
	private function isParticipant($data){
		$clause = 'WHERE meeting='.$data['id'].' AND participant='.USER_ID;
		$isParticipated = count(db_select_single_column('meeting_participant', 'id', $clause));
		if($isParticipated == 0){
			$group = $data['paricipant_group'];
			$isInGroup = count(array_intersect(ss('login_group'), $group));
			if($isInGroup) return true;
		}
		return false;
	}
	
	private function getParticipant(){
		return $this->getRelatedUser(1);
	}
	
	private function getDisclaimer(){
		return $this->getRelatedUser(0);
	}
	
	private function getRelatedUser($status){
		$clause = 'WHERE meeting='.$this->id.' AND status='.$status;
		$participant = db_select('meeting_participant', array('participant'), $clause);
		return userinfo_get_info($participant, 'participant');
	}
	
	private function isSummarizable($data){
		return (strtotime($data['meeting_date']) < time());
	}
	
	private function setAccess(){
		$this->addAction('meeting_participate', 'participate');
		$this->addAction('meeting_decline', 'decline');
		$this->addAction('meeting_participate_per_mail', 'participatePerMail');
		$this->addAction('meeting_decline_per_mail', 'declinePerMail');
		
		$this->addAccessMethod('user', 'participate');
		$this->addAccessMethod('user', 'decline');
		
		$this->addAccessMethod('guest', 'participatePerMail');
		$this->addAccessMethod('guest', 'declinePerMail');
	}
}
?>
