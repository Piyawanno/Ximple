<?php
execute_add_class('blog', 'Blog');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('BlogModel.class.inc');

class Blog extends Content{
	function Blog($isEmbed=false){
		$this->tableName = 'blog';
		$this->moduleName = 'blog';
		$this->moduleTitle = tt('Blog');
		$this->init(new BlogModel(), $isEmbed);
	}
	
	public function index($arg=null){
		if((MODE_ID and MODULE == $this->moduleName) or isset($arg['id'])){
			return $this->renderSingleBlog($arg);
		}else{
			return $this->renderMultipleBlogs($arg);
		}
	}
	
	protected function getSummary(){
		return $this->dataByID['intro'];
	}
	
	private function renderSingleBlog($arg){
		if(isset($arg['id'])) $this->id = $arg['id'];
		else $this->id = MODE_ID;
		$this->selectByID($this->column);
		if($this->isReadable()){
			if($this->dataByID['publishing_status'] < 2){
				search_set_page();
				count_increase('blog', $this->id);
			}
			$this->getSibling();
			$this->initComment();
			$this->insertTracker('read');
			$this->addMetaData();
			$this->dataByID['editable'] = $this->isEditable($this->dataByID['writer']['id']);
			$category = $this->dataByID['category']['category'];
			document_set_path($category, 'blog/tag/'.$category);
			document_set_path($this->dataByID['topic']);
			head_add_css('blog.css');
			$render = render($this->dataByID, 'singleblog.tpl', 'single_blog');
			$render.= $this->comment->render();
			document_set_title($this->dataByID['topic']);
			return $render;
		}else{
			document_set_redirect('blog');
			execute_set_db();
			notify_add_error(tt('You are not allowed to view the selected Blog.'));
		}
	}
	
	private function renderMultipleBlogs($arg){
		head_add_css('blog.css');
		$column = $this->modelConnector->getColumnNameExcepted(array('content'));
		$this->selectFirstPage($column, cc('blog_entries_number'), $arg);
		$this->getCommentNumber();
		$this->getDataEditable();
		if(!$this->isEmbed) $this->setPathMutiplePage();
		$render = render(array('data' => $this->data), 'multipleblogs.tpl', 'multiple_blogs');
		$render.= $this->pager->render('blog'.$this->getPageMode());
		return $render;
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
