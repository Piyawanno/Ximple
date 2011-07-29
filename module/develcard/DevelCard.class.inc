<?php
execute_add_class('develcard', 'DevelCard');
include('DevelCardModel.class.inc');
include('develcard.tool.inc');

class DevelCard extends Control{
	function DevelCard(){
		$this->moduleTitle = tt('DevelCard');
		$this->moduleName = 'develcard';
		$this->tableName = 'develcard';
		$this->setAccess();
		$this->setAction();
		$this->setAdmin('develcard_admin');
		$this->redirectToIDPage = true;
		$this->init(new DevelCardModel());
		$this->setConfig();
		$this->writeLabel = tt('Submit new DevelCard');
		$this->formMeta->isCaptcha = true;
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		$this->id = (int) gg('id');
		if($this->id) return $this->display();
		else return $this->summaryPage();
	}
	
	public function update(){
		Control::update();
		$this->setResolverPoint((int)pp('status'));
	}
	
	public function personalPage(){
		$id = (int) gg('id');
		if($id) return $this->rederPersonalPage();
		else return $this->rederPersonalList();
	}
	
	public function reporterListPage(){
		$uid = $this->getUserID();
		$mode = 'develcard_reporter_list/'.$uid;
		document_set_path(tt('reported by me'), $mode);
		$clause  = $this->handleStatus($mode);
		$clause .= $this->handleType($mode);
		$title = tt('DevelCard reported by me');
		$clause = 'WHERE reporter='.$uid.$clause.' ORDER BY deadline DESC';
		return $this->renderListPage($title, $clause, $mode);
	}
	
	public function resolverListPage(){
		$uid = $this->getUserID();
		$mode = 'develcard_resolver_list/'.$uid;
		document_set_path(tt('in my duty'), $mode);
		
		$clause = 'WHERE resolver='.$uid;
		$id = db_select_single_column('develcard_resolver', 'develcard', $clause);
		if(count($id)) $idClause = 'id IN ('.join(',', $id).')';
		else $idClause = 'id=0';
		
		$clause  = $this->handleStatus($mode);
		$clause .= $this->handleType($mode);
		$title = tt('DevelCard in My Duty');
		$clause = 'WHERE '.$idClause.$clause.' ORDER BY deadline DESC';
		return $this->renderListPage($title, $clause, $mode);
	}
	
	public function dropResolver(){
		db_drop('develcard_resolver', (int)gg('id'));
	}
	
	public function setStatus(){
		$this->id = (int) gg('id');
		$status = (int) gg('status');
		
		$data = array('status' => $status);
		db_update($this->tableName, $data, $this->id);
		$this->setResolverPoint($status);
		
		execute_set_db();
		document_set_redirect('develcard/'.$this->id);
		
		$statusOption = develcard_get_status_option();
		$statusName = $statusOption[$status];
		notify_add_info(tt('Status of DevelCard has been successfully changed to : ').$statusName);
	}
	
	protected function renderListPage($title, $clause, $mode){
		head_add_css('develcard.css');
		document_set_title($title);
		$this->selectPage($this->column, cc('develcard_list_per_page'), $clause);
		foreach($this->data as $key => $value){
			$this->data[$key] = $this->prepareData($value, $mode);
		}
		$renderArray = array(
			'data' => $this->data,
			'title' => $title,
			'write_icon' => $this->renderWriteIcon(),
		);
		$render = render($renderArray, 'develcard_list.tpl', 'develcard_list');
		$render.= $this->pager->render($mode);
		return $render;
	}
	
	private function renderPersonalPage(){
	
	}
	
	private function renderPersonalList(){
	
	}
	
	private function summaryPage(){
		$mode = 'develcard';
		$clause  = $this->handleStatus($mode);
		$clause .= $this->handleType($mode);
		$title = tt('DevelCard');
		$clause = 'WHERE id!=0 '.$clause.' ORDER BY id DESC';
		return $this->renderListPage($title, $clause, $mode);
	}
	
	private function display(){
		$this->selectByID($this->column);
		$this->dataByID = $this->prepareData($this->dataByID, 'develcard');
		head_add_css('develcard.css');
		document_set_path($this->dataByID['status']['label'], $this->dataByID['status_uri']);
		document_set_path($this->dataByID['type']['label'], $this->dataByID['type_uri']);
		document_set_path($this->dataByID['topic']);
		$this->dataByID['editable'] = (develcard_is_admin() or authority_group('develcard_resolver'));
		return render($this->dataByID, 'develcard_display.tpl', 'develcard_display');
	}
	
	private function setAccess(){
		$access = cc('develcard_access');
		if($access == 0){
			$this->addAccessMethod('guest', 'index');
			$this->addAccessMethod('guest', 'write');
			$this->addAccessMethod('guest', 'insert');
		}elseif($access == 1){
			$this->addAccessMethod('user', 'index');
			$this->addAccessMethod('user', 'write');
			$this->addAccessMethod('user', 'insert');
		}
		
		$this->addAccessMethod('develcard_reporter', 'index');
		$this->addAccessMethod('develcard_reporter', 'write');
		$this->addAccessMethod('develcard_reporter', 'insert');
		$this->addAccessMethod('develcard_reporter', 'reporterListPage');
		$this->addAccessMethod('develcard_reporter', 'personalPage');
		
		$this->addAccessMethod('develcard_reporter', 'index');
		$this->addAccessMethod('develcard_resolver', 'resolverListPage');
		$this->addAccessMethod('develcard_resolver', 'personalPage');
		$this->addAccessMethod('develcard_resolver', 'setStatus');
		
		$this->addAccessMethod('develcard_moderator', 'index');
		$this->addAccessMethod('develcard_moderator', 'write');
		$this->addAccessMethod('develcard_moderator', 'insert');
		$this->addAccessMethod('develcard_moderator', 'edit');
		$this->addAccessMethod('develcard_moderator', 'update');
		$this->addAccessMethod('develcard_moderator', 'drop');
		$this->addAccessMethod('develcard_moderator', 'listPage');
		$this->addAccessMethod('develcard_moderator', 'reporterListPage');
		$this->addAccessMethod('develcard_moderator', 'resolverListPage');
		$this->addAccessMethod('develcard_moderator', 'dropResolver');
		$this->addAccessMethod('develcard_moderator', 'personalPage');
		$this->addAccessMethod('develcard_moderator', 'setStatus');
	}
	
	private function prepareData($data, $mode){
		$data['type_uri'] = $this->getTypeURI($data, $mode);
		$data['status_uri'] = $this->getStatusURI($data, $mode);
		$data['priority_color'] = develcard_get_priority_color($data['priority']['value']);
		$data['residual_time'] = $this->getResidualTime($data);
		return $data;
	}
	
	private function getTypeURI($data, $mode){
		return $mode.'/status/'.$data['status']['value'].'/type/'.$data['type']['value'];
	}
	
	private function getStatusURI($data, $mode){
		return $mode.'/status/'.$data['status']['value'];
	}
	
	private function getResidualTime($data){
		$residual = ceil((strtotime($data['deadline']) - time())/(60*60*24));
		if($residual == 1) $residual = tt('tomorrow');
		elseif($residual == 0) $residual = tt('today');
		elseif($residual == -1) $residual = tt('yesterday');
		elseif($residual > 1) $residual = sprintf(tt('%d days left'), $residual);
		else $residual = sprintf(tt('%d days ago'), $residual);
		return $residual;
	}
	
	private function handleType($mode){
		$type = gg('type');
		if(strlen($type)){
			document_set_path(develcard_get_type_name($type), $mode);
			return ' AND type='.$type;
		}
	}
	
	private function handleStatus($mode){
		$status = gg('status');
		if(strlen($status)){
			document_set_path(develcard_get_status_name($status), $mode);
			return ' AND status='.$status;
		}
	}
	
	private function setAction(){
		$this->addAction('develcard_reporter_list', 'reporterListPage');
		$this->addAction('develcard_resolver_list', 'resolverListPage');
		$this->addAction('develcard_drop_resolver', 'dropResolver');
		$this->addAction('develcard_personal', 'personalPage');
		$this->addAction('develcard_set_status', 'setStatus');
	}
	
	private function setConfig(){
		$config = $this->getNewConfigForm(tt('Work Flow & Configuration'));
		$config->append('priority');
		$config->append('status');
		$config->append('resolver');
		$config->append('deadline');
	}
	
	private function getUserID(){
		$uid = (int) gg('id');
		if(empty($uid)) $uid = USER_ID;
		return $uid;
	}
	
	private function renderWriteIcon(){
		if($this->isCallable('write')){
			$this->writeLabel = sprintf(tt('Write new %s entry'), $this->moduleTitle);
			return render_write_icon('develcard_write', $this->writeLabel);
		}
	}
	
	private function setResolverPoint($status){
		$clause = 'WHERE develcard='.$this->id;
		$resolver = db_select_single_column('develcard_resolver', 'work_load', $clause);
		if($status >= 2) $this->setResolverEndPoint($status, $resolver);
		else $this->setResolverProgressPoint($status, $clause);
	}
	
	private function setResolverEndPoint($status, $resolver){
		$this->selectByID(array('deadline'));
		$deadline = strtotime($this->dataByID['deadline']);
		foreach($resolver as $key => $value){
			$point = $this->caculateResolverPoint($value, $deadline);
			$data = array(
				'status' => $status,
				'point' => $point,
				'end_date' => NOW,
			);
			db_update('develcard_resolver', $data, $key);
		}
	}
	
	private function setResolverProgressPoint($status, $clause){
		$data = array('status' => $status);
		db_update_many('develcard_resolver', $data, $clause);
	}
	
	private function caculateResolverPoint($load, $deadline){
		$difference = time() - $deadline;
		if(abs($difference) < 86400) return $load*2;
		elseif($difference < 0)	return max($load, $load*2 + ceil($difference/86400));
		else return $load*2 + ceil($difference/86400);
	}
}
?>
