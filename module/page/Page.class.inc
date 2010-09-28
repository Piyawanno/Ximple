<?php
execute_add_class('page', 'Page');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include_once(ROOT_PATH.'module/directory/directory.tool.inc');
include_once('PageModel.class.inc');

class Page extends Content{
	private $parent;
	private $parentName;
	private $configuration;
	private $pageItem;
	
	function Page($parent=null){
		$this->tableName = 'page';
		$this->moduleName = 'page';
		$this->moduleTitle = tt('Page');
		$this->setParent($parent);
		$this->init(new PageModel($this->parent), false);
	}
	
	public function index($arg){
		if(isset($arg['tag'])) $tag = $arg['tag'];
		elseif(strlen(gg('tag')) != 0) $tag = gg('tag');
		else $tag = '';
		if(strlen($tag)){
			return $this->renderTagEntries($arg, $tag);
		}else{
			if(!isset($arg['id'])) $this->id = MODE_ID;
			else $this->id = $arg['id'];
			return $this->renderSingleEntry();
		}
	}
	
	public function printPage(){
		$this->select($this->column, 'WHERE parent='.((int) gg('parent')));
		$this->setConfiguration();
		execute_set_print();
		document_set_title($this->parentName);
		$renderArray = array(
			'parent_name' => $this->parentName,
			'data' => $this->data,
			'sort' => $this->configuration['show_page'],
		);
		return render($renderArray, 'page_print.tpl', 'page_print');
	}
	
	public function write(){
		$this->setConfiguration();
		include_once(ROOT_PATH.'module/directory/directory.tool.inc');
		directory_set_path((int) gg('parent'));
		$this->modelConnector->setAttribute('comment_permission', 'configuration', $this->configuration);
		$this->modelConnector->setAttribute('publishing_status', 'configuration', $this->configuration);
		return Content::write();
	}
	
	public function edit(){
		$this->setConfiguration();
		include_once(ROOT_PATH.'module/directory/directory.tool.inc');
		directory_set_path((int) gg('parent'));
		$this->modelConnector->setAttribute('comment_permission', 'configuration', $this->configuration);
		$this->modelConnector->setAttribute('publishing_status', 'configuration', $this->configuration);
		return Content::edit();
	}
	
	public function insert(){
		Content::insert();
		$parentData = db_select_single_column('directory', 'configuration', 'WHERE id='.$this->parent);
		$configuration = unserialize($parentData[$this->parent]);
		$configuration['show_page'][] = $this->id;
		db_update('directory', array('configuration' => serialize($configuration)), $this->parent);
	}
	
	public function contributorListPage(){
		document_set_path(tt('Directory'), 'directory');
		return Content::contributorListPage();
	}
	
	public function editorListPage(){
		document_set_path(tt('Directory'), 'directory');
		return Content::editorListPage();
	}
	
	public function setParent($parent){
		if($parent) $this->parent = $parent;
		elseif(pp('parent')) $this->parent = (int) pp('parent');
		elseif(gg('parent')) $this->parent = (int) gg('parent');
	}
	
	
	public function render($renderRelated=false){
		if($this->isReadable()){
			if($this->dataByID['publishing_status'] < 2){
				search_set_page();
				count_increase('page', $this->id);
			}
			head_add_css('page.css');
			$this->initComment();
			$this->insertTracker('read');
			$this->addMetaData();
			$this->getRenderConfiguration();
			if($renderRelated) $this->renderRelatedPage();
			$this->renderSibling();
			$render = render($this->dataByID, 'page.tpl', 'page');
			$render.= $this->comment->render();
			return $render;
		}else{
			return '';
		}
	}
	
	public function renderItemList($label=null){
		$this->getPageItem();
		if(count($this->pageItem)){
			if($label == null) $label = $this->configuration['page_list_label'];
			$renderArray = array(
				'label' => $label,
				'item' => $this->pageItem,
			);
			return render($renderArray, 'page_item_list.tpl', 'page_item_list');
		}
	}
	
	public function renderDescription(){
		$this->getPageItem();
		if(count($this->pageItem)){
			head_add_css('page.css');
			return render(array('item' => $this->pageItem), 'page_description.tpl', 'page_description');
		}
	}
	
	protected function setListWriteIcon(){
	}
	
	public function setConfiguration($configuration = null){
		if($configuration!=null){
			$this->configuration = $configuration;
		}elseif($this->parent){
			$column = array('configuration', 'name');
			$parentData = db_select('directory', $column, 'WHERE id='.$this->parent, false);
			$this->configuration = unserialize($parentData[0]['configuration']);
			$this->parentName = $parentData[0]['name'];
		}
	}
	
	private function renderSingleEntry(){
		$this->selectByID($this->column);
		if($this->isReadable()){
			$this->parent = $this->dataByID['parent'];
			$this->setConfiguration();
			$render = $this->render(true);
			directory_set_path($this->dataByID['parent']);
			document_set_path($this->dataByID['topic']);
			document_set_title($this->dataByID['topic']);
			return $render;
		}else{
			document_set_redirect('directory');
			execute_set_db();
			notify_add_error(tt('You are not allowed to view the selected Page.'));
		}
	}
	
	private function renderTagEntries($arg, $tag){
		$this->selectFirstPage($this->column, 20, $arg);
		$this->getDataEditable();
		$this->getCommentNumber();
		$title = sprintf(tt('Pages tagged by %s'), $tag);
		head_add_css('page.css');
		document_set_path(tt('Directory'), 'directory');
		document_set_path($title);
		document_set_title($title);
		$renderArray = array(
			'title' => $title,
			'item' => $this->data,
		);
		return render($renderArray, 'page_tag.tpl', 'page_tag');
	}
	
	private function getPageItem(){
		$pageID = $this->configuration['show_page'];
		if(!is_array($this->pageItem) and count($pageID)){
			if(!isset($this->id)) $this->id = 0;
			$clause = 'WHERE parent='.$this->parent.' AND (id='.join(' OR id=', $pageID).') AND id!='.$this->id;
			$childPage = db_select($this->tableName, array('id', 'topic', 'uri', 'icon', 'introduction'), $clause);
			$this->pageItem = array();
			foreach($pageID as $id){
				if($id != $this->id and isset($childPage[$id])){
					$this->pageItem[$id] = $childPage[$id];
				}
			}
		}
		if(!is_array($this->pageItem)){
			$this->pageItem = array();
		}
	}
	
	private function renderRelatedPage(){
		if(in_array('related', $this->configuration['page_render_item'])){
			$label = $this->configuration['related_page_label'];
			$this->dataByID['related_page'] = $this->renderItemList($label);
		}
	}
	
	private function renderSibling(){
		if(in_array('sibling', $this->configuration['page_render_item'])){
			$pageID = $this->configuration['show_page'];
			$prePage = 0;
			$postPage = 0;
			$found = false;
			foreach($pageID as $id){
				if($id == $this->id) $found = true;
				elseif(!$found) $prePage = $id;
				else $postPage = $id;
				if($postPage) break;
			}
			$clause = 'WHERE id='.$prePage.' OR id='.$postPage;
			$sibling = db_select($this->tableName, array('id', 'topic', 'uri'), $clause);
			if(isset($sibling[$prePage])) $this->dataByID['back'] = $sibling[$prePage];
			if(isset($sibling[$postPage])) $this->dataByID['next'] = $sibling[$postPage];
		}
	}
	
	private function getRenderConfiguration(){
		$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
		$renderItem = $this->configuration['page_render_item'];
		$this->dataByID['show_introduction'] = in_array('introduction', $renderItem);
		$this->dataByID['show_avatar'] = in_array('avatar', $renderItem);
		$this->dataByID['show_category'] = in_array('category', $renderItem);
	}
}
?>
