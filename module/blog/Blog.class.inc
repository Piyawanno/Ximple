<?php
execute_add_class('blog', 'Blog');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('BlogModel.class.inc');

class Blog extends Content{
	function Blog(){
		$this->tableName = 'blog';
		$this->moduleName = 'blog';
		$this->moduleTitle = tt('Blog');
		$this->init(new BlogModel());
	}
	
	public function index(){
		document_set_path($this->moduleTitle, $this->moduleName);
		if($this->isSingleEntry()) return $this->renderSingleBlog();
		else return $this->renderMultipleBlogs();
	}
	
	public function printPage(){
		$this->id = MODE_ID;
		$this->selectByID($this->column);
		execute_set_print();
		document_set_title($this->dataByID['topic']);
		$this->dataByID['content'] = $this->dataByID['intro'].$this->dataByID['content'];
		return render($this->dataByID, 'content_print.tpl', 'blog_print');
	}
	
	protected function getSummary(){
		return $this->dataByID['intro'];
	}
	
	private function renderSingleBlog(){
		$this->id = mid();
		$this->selectByID($this->column);
		if($this->isReadable()) return $this->executeRender();
		else $this->accessDeniedEntry();
	}
	
	private function renderMultipleBlogs(){
		head_add_css('blog.css');
		$column = $this->modelConnector->getColumnNameExcepted(array('content'));
		$this->selectFirstPage($column, cc('blog_entries_number'));
		$this->getCommentNumber();
		$this->getDataEditable();
		$this->setPathMutiplePage();
		$render = render(array('data' => $this->data), 'multipleblogs.tpl', 'multiple_blogs');
		$render.= $this->pager->render('blog'.$this->getPageMode());
		return $render;
	}
	
	private function executeRender(){
		head_add_css('blog.css');
		$this->prepareRender();
		$render = render($this->dataByID, 'singleblog.tpl', 'single_blog');
		$render.= $this->comment->render();
		$this->setDocumentData();
		return $render;
	}
	
	private function prepareRender(){
		$this->handlePublishingStatus();
		$this->getSibling();
		$this->initComment();
		$this->insertTracker('read');
		$this->addMetaData();
		$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
	}
	
	private function getSibling(){
		$publishTime = $this->dataByID['unformatted_publish_time'];
		$clause = 'WHERE (section='.SECTION." AND publish_time > '$publishTime' AND publishing_status < 2) ";
		$clause.= 'ORDER BY publish_time LIMIT 1';
		$next = db_select('blog', array('id', 'topic', 'uri'), $clause);
		$clause = 'WHERE (section='.SECTION." AND publish_time < '$publishTime' AND publishing_status < 2) ";
		$clause.= 'ORDER BY publish_time DESC LIMIT 1';
		$back = db_select('blog', array('id', 'topic', 'uri'), $clause);
		$this->dataByID['next'] = array_values($next);
		$this->dataByID['back'] = array_values($back);
	}
}
?>
