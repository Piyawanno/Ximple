<?php
execute_add_extended_class('peopleinfo', 'info', 'Information');

include_once('InformationModel.class.inc');
include_once('peopleinfo.tool.inc');

class Information extends Control{
	function Information($setPath=true){
		$this->moduleTitle = tt('Information');
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'info';
		$this->tableName = 'information';
		$this->setAccess();
		$this->redirectToIDPage = true;
		$this->init(new InformationModel());
		if($setPath){
			document_set_path(tt('People Information Center'), 'peopleinfo_summary');
			document_set_path(tt('Information'), 'peopleinfo_info');
		}
	}
	
	public function index(){
		$this->id = (int) gg('id');
		$tag = gg('tag');
		if($this->id) return $this->renderPage();
		elseif(strlen($tag)) return $this->renderTag($tag);
		else return $this->renderListPage();
	}
	
	public function renderListPage(){
		document_set_path(tt('List of Information'));
		$this->listMeta->title = tt('List of Information');
		$this->listMeta->mode = 'peopleinfo_info_list';
		$this->selectListPage(20, 'WHERE section='.SECTION);
		$this->setListWriteIcon(tt('Add Information'), 'peopleinfo_info_write');
		$this->setListEditIcon();
		$this->setListDropIcon();
		return Control::renderListPage();
	}
	
	public function write(){
		$this->setConfigForm();
		return Control::write();
	}
	
	public function insert(){
		Control::insert();
		$this->renameFile();
	}
	
	public function edit(){
		$this->setConfigForm();
		return Control::edit();
	}
	
	public function update(){
		Control::update();
		$this->renameFile();
	}
	
	public function drop(){
		db_drop_many('people_relation', 'information='.gg('id'));
		db_drop_many('event_relation', 'information='.gg('id'));
		$file = db_select_single_column('people_file', 'file', 'WHERE information='.gg('id'), false);
		foreach($file as $key => $value){
			if(is_file(ROOT_PATH.$value)) unlink(ROOT_PATH.$value);
		}
		$dirName = ROOT_PATH.dirname($file[0]);
		if(is_dir($dirName)) rmdir($dirName);
		db_drop_many('people_file', 'information='.gg('id'));
		Control::drop();
	}
	
	public function readFile(){
		$clause = 'WHERE id='.((int) gg('id'));
		$data = db_select('people_file', array('file', 'short_description'), $clause);
		$fileName = ROOT_PATH.$data[0]['file'];
		$mime = mime_content_type($fileName);
		$extension = array_pop(split('\.', $data[0]['file']));
		header('Content-type: '.$mime);
		header('Content-Disposition: attachment; filename="'.$data[0]['short_description'].'.'.$extension.'"');
		readfile($fileName);
		execute_set_file();
	}
	
	public function dropPeopleRelation(){
		db_drop('people_relation', (int) gg('id'));
	}
	
	public function dropEventRelation(){
		db_drop('event_relation', (int) gg('id'));
	}
	
	public function dropPeopleFile(){
		$file = db_select_single_column('people_file', 'file', 'WHERE id='.gg('id'), false);
		if(is_file(ROOT_PATH.$file[0])) unlink(ROOT_PATH.$file[0]);
		db_drop('people_file', (int) gg('id'));
	}
	
	public function renderPeopleInformation($peopleID){
		head_add_css('form.css');
		$clause = 'WHERE people='.$peopleID;
		$informationID = db_select_single_column('people_relation', 'information', $clause);
		if(count($informationID)){
			return $this->renderMultiple($informationID);
		}
	}
	
	public function renderEventInformation($eventID){
		head_add_css('form.css');
		$clause = 'WHERE event='.$eventID;
		$informationID = db_select_single_column('event_relation', 'information', $clause);
		if(count($informationID)){
			return $this->renderMultiple($informationID);
		}
	}
	
	private function renderTag($tag){
		$data = peopleinfo_get_tagged($tag, 'peopleinfo_info', 'information', 'topic');
		$renderArray = array(
			'data' => $data,
			'module' => $this->moduleTitle,
			'mode' => 'peopleinfo_info',
			'tag' => $tag
		);
		return render($renderArray, 'peopleinfo_tag_list.tpl', 'peopleinfo_tag_list_information');
	}
	
	private function renderMultiple($idArray){
		$clause = 'WHERE id='.join(' OR id=', $idArray);
		$this->select($this->column, $clause);
		$renderPages = array();
		$renderArray = array(
			'show_header' => false,
			'editable' => authority_group('peopleinfo_admin'),
		);
		foreach($this->data as $id => $data){
			list($data, $image) = $this->separateImageFile($data);
			$renderArray['image'] = $image;
			$renderArray['data'] = $data;
			$render = render($renderArray, 'peopleinfo_info.tpl', 'peopleinfo_info_part');
			$renderPages['pages'][$id]['topic'] = $data['topic'];
			$renderPages['pages'][$id]['page']  = $render;
		}
		return render($renderPages, 'peopleinfo_muliple.tpl', 'peopleinfo_multiple_info');
	}
	
	private function renderPage(){
		head_add_css('peopleinfo.css');
		search_set_page();
		$this->id = (int) gg('id');
		$this->selectByID($this->column);
		list($this->dataByID, $image) = $this->separateImageFile($this->dataByID);
		document_set_path($this->dataByID['topic']);
		$renderArray = array(
			'show_header' => true,
			'image' => $image,
			'data' => $this->dataByID,
			'editable' => authority_group('peopleinfo_admin'),
		);
		return render($renderArray, 'peopleinfo_info.tpl', 'peopleinfo_info');
	}
	
	private function separateImageFile($data){
		$image = array();
		foreach($data['file'] as $key => $value){
			if(substr($value['type'], 0, 5) == 'image'){
				$image[$key] = $value;
				unset($data['file'][$key]);
			}
		}
		return array($data, $image);
	}
	
	private function setAccess(){
		$this->dropAccessMethod('index');
		$this->setAdmin('peopleinfo_admin');
		
		$this->addAction('peopleinfo_info_file', 'readFile');
		$this->addAction('peopleinfo_info_drop_people_relation', 'dropPeopleRelation');
		$this->addAction('peopleinfo_info_drop_event_relation', 'dropEventRelation');
		$this->addAction('peopleinfo_info_drop_people_file', 'dropPeopleFile');
		
		$this->addAccessMethod('index', 'peopleinfo_observer');
		$this->addAccessMethod('listPage', 'peopleinfo_observer');
		$this->addAccessMethod('readFile', 'peopleinfo_observer');
	}
	
	private function setConfigForm(){
		$people = $this->getNewConfigForm(tt('related people'));
		$people->append('people');
		
		$event = $this->getNewConfigForm(tt('related events'));
		$event->append('event');
		
		$file = $this->getNewConfigForm(tt('related files'));
		$file->append('file');
	}
	
	private function renameFile(){
		$clause = 'WHERE information='.$this->id;
		$peopleFile = db_select_single_column('people_file', 'file', $clause);
		$dirName  = 'files/peopleinfo/'.(rand()%65536).'/';
		if(!is_dir($dirName)) mkdir($dirName);
		$oldDir = '';
		foreach($peopleFile as $key => $value){
			$type = io_get_file_extension($value);
			$fileName = $dirName.md5(rand()).sha1(rand()).md5(rand()).'.'.$type;
			$success = true;
			$oldDir = ROOT_PATH.dirname($value);
			@rename(ROOT_PATH.$value, ROOT_PATH.$fileName) or $success = false;
			if($success){
				$size = filesize(ROOT_PATH.$fileName);
				db_update('people_file', array('file' => $fileName), $key);
			}
		}
		@rmdir($oldDir);
	}
}
?>
