<?php
execute_add_class('category', 'Category');
include('CategoryModel.class.inc');

class Category extends Control{
	private $mode;
	private $modeName;
	private $indexMode;
	
	function Category(){
		$this->tableName = 'category';
		$this->moduleName = 'category';
		$this->moduleTitle = tt('Category');
		$this->init(new CategoryModel(gg('module')), false);
	}
	
	function index(){
		$modeName = cc('module_name');
		$contentType = $modeName[$this->mode];
		
		$description = sprintf(tt('With this page, you can manage Categories for %s. '), $contentType);
		$description.= tt('Every content entry can be allocated with a Category and many Tags for the efficient content management.');
		$this->listMeta->description = $description;
		$this->listMeta->title = sprintf(tt('List of %s for %s'), $this->moduleTitle, $contentType);
		$this->listMeta->defaultOrder = 'id';
		$this->listMeta->mode = $this->indexMode;
		
		$writeMode = 'category_write/module/'.$this->mode;
		$this->setListWriteIcon(sprintf(tt('Add new Category for %s'), $contentType), $writeMode);
		$this->setListEditIcon();
		$this->selectListPage(5, 'WHERE (section='.SECTION." and mode='".$this->mode."')");
		return $this->renderListPage();
	}
	
	public function isCallable($methodName){
		$this->mode = gg('module');
		if(!$this->mode) $this->mode = pp('mode');
		if(!$this->mode) $this->mode = $this->dataByID['mode'];
		
		$mode_require = cc('module_require');
		if(!isset($mode_require[$this->mode])){
			error_syslog('The called mode for category does not exist.');
		}
		
		$this->indexMode = 'category/module/'.$this->mode;
		$this->setAdmin($this->mode.'_admin');
		$this->uriMode = 'category/module/'.$this->mode;
		
		$moduleName = cc('module_name');
		$this->modeName = $moduleName[$this->mode];
		document_set_path($this->modeName, $this->mode);
		document_set_path($this->moduleTitle, $this->indexMode);
		document_set_title($this->moduleTitle);
		
		$this->insertRedirection = $this->indexMode;
		$this->updateRedirection = $this->indexMode;
		
		return Authority::isCallable($methodName);
	}
}
?>
