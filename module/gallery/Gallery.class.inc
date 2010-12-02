<?php
execute_add_class('gallery', 'Gallery');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('GalleryModel.class.inc');

class Gallery extends Content{
	private $galleryPicture;
	
	function Gallery($isEmbed=false){
		$this->tableName = 'gallery';
		$this->moduleName = 'gallery';
		$this->moduleTitle = tt('Gallery');
		$this->init(new GalleryModel(), $isEmbed);
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		if($this->isSingleEntry()) return $this->renderSingleGallery();
		else return $this->renderMultipleGalleries();
	}
	
	private function renderSingleGallery(){
		$this->id = mid();
		$this->selectByID($this->column);
		if($this->isReadable()){
			$this->prepareRender();
			head_add_css('gallery.css');
			require_once('GalleryPicture.class.inc');
			$this->galleryPicture = new GalleryPicture($this->id);
			$this->getPictures();
			$this->getPictureForm();
			$this->getAppearanceConfiguration();
			$render = render($this->dataByID, 'singlegallery.tpl', 'single_gallery');
			$render.= $this->comment->render();
			$this->setDocumentData();
			return $render;
		}else{
			$this->accessDeniedEntry();
		}
	}
	
	private function renderMultipleGalleries(){
		head_add_css('gallery.css');
		$column = $this->modelConnector->getColumnNameExcepted(array('content'));
		$this->selectFirstPage($column, cc('gallery_entries_number'));
		$this->getCommentNumber();
		$this->getDataEditable();
		$this->setPathMutiplePage();
		$render = render(array('data' => $this->data), 'multiplegallerys.tpl', 'multiple_gallerys');
		$render.= $this->pager->render('gallery'.$this->getPageMode());
		return $render;
	}
	
	private function prepareRender(){
		$this->handlePublishingStatus();
		$this->initComment();
		$this->insertTracker('read');
		$this->addMetaData();
		$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
	}
	
	private function getPictureForm(){
		if($this->isCallable('update')){
			$this->dataByID['picture_form'] = $this->galleryPicture->renderInsertForm();
		}
	}
	
	private function getPictures(){
	}
	
	private function getAppearanceConfiguration(){
		$appearance = cc('gallery_appearance');
		if(!is_array($appearance)) $appearance = array();
		$this->dataByID['show_avatar'] = in_array('avatar', $appearance);
		$this->dataByID['show_category'] = in_array('category_icon', $appearance);
		$this->dataByID['show_sibling'] = in_array('sibling', $appearance);
	}
}
?>
