<?php
abstract class OverlayControl extends Control{
	protected $parentColumn;
	protected $parentID;
	protected $overlayDescription;
	
	public function init($modelObject){
		Control::init($modelObject);
		$this->setAction();
		$this->overlayDescription = sprintf(tt('You can use this table to manage entry of %s'), $this->moduleTitle);
	}
	
	public function getJavaScript(){
		$this->modelConnector->triggerGetJavaScript();
	}
	
	public function overlayWrite(){
		execute_set_ajax();
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'overlaySubmitForm';
		return $this->write();
	}
	
	public function overlayEdit(){
		execute_set_ajax();
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'overlaySubmitForm';
		return $this->edit();
	}
	
	public function overlayRefresh(){
		execute_set_ajax();
		$this->getOverlayData();
		$renderArray = array(
			'data' => $this->data,
			'label' => $this->modelConnector->getColumnAttribute('label'),
			'module' => $this->fullModuleName,
			'column' => $this->column,
			'description' => $this->overlayDescription,
		);
		return render($renderArray, 'overlay_list.tpl', 'overlay_list');
	}
	
	protected function getOverlayData(){
		$this->getOverlayColumn();
		$clause = $this->getParentClause();
		if(strlen($clause)) $this->select($this->column, $clause);
		else $this->data = array();
	}
	
	protected function getOverlayColumn(){
		$this->column = $this->modelConnector->getColumnNameByBoolean('isList');
	}
	
	protected function getParentClause(){
		$this->parentColumn = $this->modelConnector->getParentColumnName();
		$this->parentID = (int) gg('parent');
		if($this->parentID){
			return 'WHERE '.$this->parentColumn.'='.$this->parentID;
		}else{
			return null;
		}
	}
	
	private function setAction(){
		$this->addAction($this->fullModuleName.'_overlay_write', 'overlayWrite');
		$this->addAction($this->fullModuleName.'_overlay_edit', 'overlayEdit');
		$this->addAction($this->fullModuleName.'_overlay_refresh', 'overlayRefresh');
	}
}
?>
