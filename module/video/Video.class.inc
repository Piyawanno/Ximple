<?php
execute_add_class('video', 'Video');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('VideoModel.class.inc');

class Video extends Content{
	function Video(){
		$this->tableName = 'video';
		$this->moduleName = 'video';
		$this->moduleTitle = tt('Video');
		$this->init(new VideoModel(), false);
	}
	
	public function index($arg=null){
		if($arg == null){
			document_set_path($this->moduleTitle, $this->moduleName);
			document_set_title($this->moduleTitle);
		}
		if(MODE_ID){
			return $this->renderSingleVideo($arg);
		}else{
			return $this->renderMultipleVideos($arg);
		}
	}
	
	public function renderSingleVideo($arg){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		if($this->isReadable()){
			if($this->dataByID['publishing_status'] < 2){
				search_set_page();
				count_increase('video', MODE_ID);
			}
			$this->initComment();
			$this->insertTracker('read');
			$this->addMetaData();
			$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
			$category = $this->dataByID['category']['category'];
			if($arg == null){
				document_set_path($category, 'video/tag/'.$category);
				document_set_path($this->dataByID['topic']);
			}
			head_add_css('video.css');
			$render = render($this->dataByID, 'singlevideo.tpl', 'single_video');
			$render.= $this->comment->render();
			document_set_title($this->dataByID['topic']);
			return $render;
		}else{
			document_set_redirect('video');
			execute_set_db();
			notify_add_error(tt('You are not allowed to view the selected Video.'));
		}
	}
	
	private function renderMultipleVideos($arg){
		head_add_css('video.css');
		$this->selectFirstPage($this->column, cc('video_entries_number'));
		$this->getCommentNumber();
		$this->getDataEditable();
		if($arg == null) $this->setPathMutiplePage();
		$render = render(array('data' => $this->data), 'multiplevideos.tpl', 'multiple_videos');
		$render.= $this->pager->render('video'.$this->getPageMode());
		return $render;
	}
	
	public function insert(){
		$file = ff('file');
		if($file['size'] == 0 or $file['type'] == 'video/x-flv'){
			Content::insert();
			$this->selectByID($this->column);
			$size = filesize(ROOT_PATH.$this->dataByID['file']);
			db_update($this->tableName, array('size' => $size), $this->id);
		}else{
			notify_add_error(tt('Video support only .flv file.'));
		}
	}
	
	public function update(){
		$file = ff('file');
		if($file['size'] == 0 or $file['type'] == 'video/x-flv'){
			Content::update();
			$this->selectByID($this->column);
			$size = filesize(ROOT_PATH.$this->dataByID['file']);
			db_update($this->tableName, array('size' => $size), $this->id);
		}else{
			notify_add_error(tt('Video support only .flv file.'));
		}
	}
}

?>
