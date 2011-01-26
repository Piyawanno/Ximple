<?php

include_once('Translatable.class.inc');
include_once('Model.class.inc');
include_once('ModelFactory.class.inc');
include_once('ModelConnector.class.inc');
include_once('FormMetaData.class.inc');
include_once('ListPageMetaData.class.inc');

abstract class Control extends Translatable{
	private $formRender;
	private $prepareMethodMap = array();
	private $tableCreator;
	private $listPage;
	private $modelHasCategory;
	
	
	protected $data;
	protected $dataByID;
	protected $listMeta;
	protected $tableName;
	
	protected $ownerColumn;
	protected $dataModifier;
	protected $pager;
	
	protected $insertRedirection;
	protected $updateRedirection;
	protected $dropRedirection;
	
	protected $writeLabel;
	protected $editLabel;
	
	protected $insertNotify;
	protected $updateNotify;
	protected $dropNotify;
	
	public $id;
	public $column;
	
	public function index(){
		$this->selectListPage(20, 'WHERE (section='.SECTION.')');
		return $this->renderDefaultListPage();
	}
	
	public function write(){
		$this->formMeta->id = $this->moduleName;
		if($this->writeLabel) $this->formMeta->title = $this->writeLabel;
		else $this->formMeta->title = sprintf(tt('Add %s'), $this->moduleTitle);
		$this->formMeta->mode = $this->moduleName.'_insert';
		$render = $this->renderInsertForm();
		document_set_path($this->formMeta->title);
		return $render;
	}
	
	public function edit(){
		$this->formMeta->id = $this->moduleName;
		if($this->editLabel) $this->formMeta->title = $this->editLabel;
		else $this->formMeta->title = sprintf(tt('Edit %s'), $this->moduleTitle);
		$this->formMeta->mode = $this->moduleName.'_update';
		$render = $this->renderUpdateForm();
		document_set_path($this->formMeta->title);
		return $render;
	}
	
	public function insert(){
		$this->initDataModifier();
		$this->dataModifier->prepareInsert();
		$insertOk = $this->dataModifier->insert($this->formMeta->isCaptcha);
		document_set_redirect($this->insertRedirection);
		if($insertOk){
			$this->id = $this->dataModifier->getID();
			notify_add_info($this->insertNotify);
		}
	}
	
	public function update(){
		$this->initDataModifier();
		$this->dataModifier->prepareUpdate();
		$updateOk = $this->dataModifier->update($this->formMeta->isCaptcha);
		document_set_redirect($this->updateRedirection);
		if($updateOk){
			notify_add_info($this->updateNotify);
		}
	}
	
	public function drop(){
		$this->initDataModifier();
		$this->dataModifier->prepareDrop();
		$this->dataModifier->drop();
		document_set_redirect($this->dropRedirection);
		notify_add_info($this->dropNotify);
	}
	
	public function prepareMethod($methodName){
		if(isset($this->prepareMethodMap[$methodName])){
			$prepare = $this->prepareMethodMap[$methodName];
			$this->$prepare();
		}
	}
	
	public function prepareModifyDB(){
		$this->id = (int)gg('id');
		if(empty($this->id)) error_syslog(tt('Data can not be prepared without any given ID.'));
		$this->selectByID($this->column, true);
		if(!count($this->dataByID)) error_syslog(tt('The selected data is empty.'));
		if($this->ownerColumn) $this->setOwner($this->dataByID[$this->ownerColumn]);
		$this->modelConnector->setData($this->dataByID);
	}
	
	public function initModule($requirement){
		if(!$this->tableCreator){
			include_once('TableCreator.class.inc');
			$this->tableCreator = new TableCreator($this->modelConnector, $this->tableName);
			if($this->modelHasCategory){
				require_once(ROOT_PATH.'include/tool/category.tool.inc');
				category_init('download');
			}
		}
		$this->tableCreator->create();
		module_add($this->moduleName, $requirement, $this->moduleTitle);
	}
	
	public function dropModule(){
		module_drop($this->moduleName);
	}
	
	public function select($col, $clause=null){
		$this->checkColumnExist($col);
		$this->data = db_select($this->tableName, $col, $clause);
		$this->postSelect();
	}
	
	public function selectSingleColumn($col, $clause=null){
		$this->checkColumnExist(array($col));
		$this->select(array('id', $col), $clause);
		$data = array();
		foreach($this->data as $key => $value){
			$data[$key] = $value[$col];
		}
		return $data;
	}
	
	public function selectByID($col, $isRaw=false){
		$this->checkColumnExist($col);
		$this->data = db_select($this->tableName, $col, 'WHERE id='.(int)$this->id);
		if(!$isRaw) $this->postSelect();
		if(isset($this->data[$this->id])){
			$this->dataByID = $this->data[$this->id];
		}else{
			error_not_found();
		}
	}
	
	public function selectPage($col, $pageLength, $clause=null){
		$this->checkColumnExist($col);
		$rowsNumber = db_get_rows_number($this->tableName, $clause);
		if(!$this->pager){
			include_once('PagerRender.class.inc');
			$this->pager = new PagerRender();
		}
		$this->pager->setPageLength($pageLength);
		$this->pager->setRowsNumber($rowsNumber);
		
		$clause .= ' LIMIT '.(int)$pageLength.' OFFSET '.(int)(MODE_PAGE*$pageLength);
		$this->data = db_select($this->tableName, $col, $clause);
		$this->postSelect();
	}
	
	protected function init($modelObj){
		$this->modelHasCategory = $modelObj->hasCategory();
		
		if(empty($this->insertRedirection)) $this->insertRedirection = $this->moduleName;
		if(empty($this->updateRedirection)) $this->updateRedirection = $this->moduleName;
		if(empty($this->dropRedirection)) $this->dropRedirection = $this->moduleName;
		
		$this->addAction($this->moduleName, 'index');
		$this->addAction($this->moduleName.'_list', 'listPage');
		$this->addAction($this->moduleName.'_write', 'write');
		$this->addAction($this->moduleName.'_edit', 'edit');
		$this->addAction($this->moduleName.'_insert', 'insert');
		$this->addAction($this->moduleName.'_update', 'update');
		$this->addAction($this->moduleName.'_drop', 'drop');
		$this->addAction($this->moduleName.'_print', 'printPage');
		$this->addAction($this->moduleName.'_translate_form', 'renderTranslateForm');
		$this->addAction($this->moduleName.'_translate', 'setTranslate');
		
		$this->prepareMethodMap['edit'] = 'prepareModifyDB';
		$this->prepareMethodMap['update'] = 'prepareModifyDB';
		$this->prepareMethodMap['drop'] = 'prepareModifyDB';
		
		$modelFactory = new ModelFactory($this->moduleName, $modelObj);
		$this->modelConnector = $modelFactory->bind();
		$this->column = $this->modelConnector->getColumnName();
		$this->formMeta = new FormMetaData();
		$this->listMeta = new ListPageMetaData();
		
		if(empty($this->insertNotify)){
			$this->insertNotify = sprintf(tt('%s has been successfully inserted.'), $this->moduleTitle);
		}
		if(empty($this->updateNotify)){
			$this->updateNotify = sprintf(tt('%s has been successfully updated.'), $this->moduleTitle);
		}
		if(empty($this->dropNotify)){
			$this->dropNotify = sprintf(tt('%s has been successfully dropped.'), $this->moduleTitle);
		}
	}
	
	protected function setListWriteIcon($label=null, $mode=null){
		if($this->isCallable('write')){
			if(empty($label)) $label = sprintf(tt('Add %s'), $this->moduleTitle);
			if(empty($mode)) $mode = $this->moduleName.'_write';
			$this->listMeta->writeLabel = $label;
			$this->listMeta->writeMode = $mode;
		}
	}
	
	protected function setListEditIcon($label=null, $mode=null){
		if($this->isCallable('edit')){
			if(empty($label)) $label = tt('edit');
			if(empty($mode)) $mode = $this->moduleName.'_edit';
			$this->listMeta->addOperation($mode, $label, 'edit.png');
		}
	}
	
	protected function setListDropIcon($label=null, $mode=null){
		if($this->isCallable('drop')){
			if(empty($label)) $label = tt('drop');
			if(empty($mode)) $mode = $this->moduleName.'_drop';
			$this->listMeta->addOperation($mode, $label, 'drop.png');
		}
	}
	
	public function selectListPage($pageLength=20, $where=null, $additionColumn=array()){
		$this->initListPage();
		$col = $this->modelConnector->getColumnNameByBoolean('isList');
		$col = array_merge(array('id'), $col);
		$col = array_unique(array_merge($col, $additionColumn));
		$this->selectPage($col, $pageLength, $this->listPage->getClause($where));
	}
	
	protected function renderDefaultListPage($description=null){
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->mode = $this->moduleName;
		$this->listMeta->defaultOrder = 'id';
		$this->listMeta->description = $description;
		$this->setListWriteIcon();
		$this->setListEditIcon();
		$this->setListDropIcon();
		return $this->renderListPage();
	}
	
	protected function renderListPage(){
		$this->initListPage();
		$this->renderImage();
		$render = $this->listPage->render($this->data);
		$render.= $this->pager->render($this->listPage->getPageMode());
		$render.= $this->listPage->renderSearchForm();
		return $render;
	}
	
	protected function setPrepareAction($methodName, $prepareMethodName){
		$this->prepareMethodMap[$mode] = $methodName;
	}
	
	protected function getNewConfigForm($title, $description=null){
		if(!$this->modelConnector and state_is_develop()) {
			$message  = 'You should call Control::createModel';
			$message .= 'before calling Control::initConfigForm().';
			notify_add_error($message);
		}
		include_once('ConfigFormRender.class.inc');
		$configForm = new ConfigFormRender($this->modelConnector, $title, $description);
		$this->configForm[] = $configForm;
		return $configForm;
	}
	
	protected function renderInsertForm($setPath=true){
		$this->prepareForm($setPath);
		return $this->formRender->renderInsertForm();
	}
	
	protected function renderUpdateForm($setPath=true){
		$this->unserializeData();
		$this->prepareForm($setPath);
		if(isset($this->data[$this->id])){
			$this->formMeta->mode .= '/'.$this->id.'/page/'.MODE_PAGE;
			return $this->formRender->renderUpdateForm($this->data[$this->id]);
		}elseif(state_is_develop()){
			notify_add_error('No data for update-form rendering.');
		}
	}
	
	protected function createTable(){
		if(!$this->tableCreator){
			include_once('TableCreator.class.inc');
			$this->tableCreator = new TableCreator($this->modelConnector, $this->tableName);
		}
		$this->tableCreator->create();
	}
	
	protected function postSelect(){
		$this->formatDateTime();
		$this->unserializeData();
		$this->data = $this->modelConnector->triggerSelect($this->data);
	}
	
	private function prepareForm(){
		if(!$this->formRender){
			include_once('FormRender.class.inc');
			$this->formRender = new FormRender($this->modelConnector, $this->formMeta);
		}
		$this->formMeta->configForm = $this->configForm;
		if($this->formMeta->isSetTitle){
			document_set_title($this->formMeta->title);
		}
	}
	
	private function formatDateTime(){
		$timeColumns = $this->modelConnector->getColumnNameByAttribute('type', 'timestamp');
		$dateColumns = $this->modelConnector->getColumnNameByAttribute('type', 'date');
		$dateFormat = $this->modelConnector->getColumnAttribute('dateFormat');
		$columns = array_merge($timeColumns, $dateColumns);
		foreach($columns as $column){
			foreach($this->data as $key => $value){
				if(isset($value[$column])){
					$this->data[$key]['unformatted_'.$column] = $value[$column];
					$formatted = date($dateFormat[$column], strtotime($value[$column]));
					$this->data[$key][$column] = $formatted;
				}
			}
		}
	}
	
	private function unserializeData(){
		$columns = $this->modelConnector->getColumnNameByBoolean('isSerialize');
		foreach($columns as $column){
			foreach($this->data as $key => $value){
				if(isset($value[$column]) and !is_array($value[$column])){
					$this->data[$key][$column] = unserialize($value[$column]);
				}
			}
		}
	}
	
	private function renderImage(){
		$columns = $this->modelConnector->getColumnNameByBoolean('isImage');
		$p = '<img alt="%s" src="%s" border="0" />';
		foreach($columns as $column){
			foreach($this->data as $key => $value){
				if(isset($value[$column])){
					$this->data[$key][$column] = sprintf($p, $column, ROOT_URI.$value[$column]);
				}
			}
		}
	}
	
	private function initDataModifier(){
		if(!$this->dataModifier){
			include_once('DataModifier.class.inc');
			$this->dataModifier = new DataModifier($this->tableName, $this->modelConnector);
		}
		execute_set_db();
	}
	
	private function initListPage(){
		if(!$this->listPage){
			include_once('ListPage.class.inc');
			$this->listPage = new ListPage($this->modelConnector, $this->listMeta);
		}
	}
	
	private function checkColumnExist($columns){
		if(!state_is_develop()) return null;
		foreach($columns as $col){
			if(!in_array($col, $this->column)){
				notify_add_error('Selected column : '.$col.' ( in '.$this->moduleName.') does not exist.');
			}
		}
	}
}
?>
