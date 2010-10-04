<?php
execute_add_class('gallery', 'Gallery');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('GalleryModel.class.inc');

class Gallery extends Content{
	function Gallery($isEmbed=false){
		$this->tableName = 'gallery';
		$this->moduleName = 'gallery';
		$this->moduleTitle = tt('Gallery');
		$this->init(new GalleryModel(), $isEmbed);
	}
	
	public function index($arg=null){
		if((MODE_ID and MODULE == $this->moduleName) or isset($arg['id'])){
			return $this->renderSingleGallery($arg);
		}else{
			return $this->renderMultipleGalleries($arg);
		}
	}
	
	private function renderSingleGallery($arg){
		if(isset($arg['id'])) $this->id = $arg['id'];
		else $this->id = MODE_ID;
		$this->selectByID($this->column);
		if($this->isReadable()){
			if($this->dataByID['publishing_status'] < 2){
				search_set_page();
				count_increase('gallery', $this->id);
			}
			$this->getSibling();
			$this->initComment();
			$this->insertTracker('read');
			$this->addMetaData();
			$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
			$category = $this->dataByID['category']['category'];
			document_set_path($category, 'gallery/tag/'.$category);
			document_set_path($this->dataByID['topic']);
			head_add_css('gallery.css');
			$render = render($this->dataByID, 'singlegallery.tpl', 'single_gallery');
			$render.= $this->comment->render();
			document_set_title($this->dataByID['topic']);
			return $render;
		}else{
			document_set_redirect('gallery');
			execute_set_db();
			notify_add_error(tt('You are not allowed to view the selected Gallery.'));
		}
	}
	
	private function renderMultipleGalleries($arg){
		head_add_css('gallery.css');
		$column = $this->modelConnector->getColumnNameExcepted(array('content'));
		$this->selectFirstPage($column, cc('gallery_entries_number'), $arg);
		$this->getCommentNumber();
		$this->getDataEditable();
		if(!$this->isEmbed) $this->setPathMutiplePage();
		$render = render(array('data' => $this->data), 'multiplegallerys.tpl', 'multiple_gallerys');
		$render.= $this->pager->render('gallery'.$this->getPageMode());
		return $render;
	}
}
?>
