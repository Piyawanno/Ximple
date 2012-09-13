<?php
abstract class OverlayControl extends Control{
	protected $parentColumn;
	protected $parentID;
	protected $overlayDescription;
	
	public function init($modelObject){
		Control::init($modelObject);
		$this->setAction();
		$this->overlayDescription = sprintf(tt('You can use this table to manage entry of %s'), $this->moduleTitle);
		$this->prepareMethodMap['overlayEdit'] = 'prepareModifyDB';
	}
	
	public function getJavaScript(){
		$this->modelConnector->triggerGetJavaScript();
	}
	
	public function overlayInsert(){
		$this->insert();
		if(!state_is_develop()){
			execute_set_ajax();
			ob_end_clean();
			return $this->fullModuleName.'/'.$this->tableName.'/'.$this->id;
		}else{
			execute_set_db();
		}
	}
	
	public function overlayWrite(){
		execute_set_ajax();
		$this->modelConnector->setAsOverlayGridForm();
		$this->parentID = (int) gg('parent');
		$this->modelConnector->setParentID($this->parentID);
		$this->modelConnector->triggerSetParent();
		$this->formMeta->mode = $this->fullModuleName.'_overlay_insert';
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'overlayInsertForm';
		return $this->write();
	}
	
	public function overlayEdit(){
		execute_set_ajax();
		$this->modelConnector->setAsOverlayGridForm();
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'overlayUpdateForm';
		return $this->edit();
	}
	
	public function overlayRefresh(){
		execute_set_ajax();
		$this->getOverlayData();
		$renderArray = array(
			'data' => $this->data,
			'label' => $this->modelConnector->getColumnAttribute('label'),
			'module' => $this->fullModuleName,
			'column' => $this->overlayColumn,
			'form_id' => gg('form_id'),
			'description' => $this->overlayDescription,
		);
		return render($renderArray, 'overlay_list.tpl', 'overlay_list');
	}
	
	public function getModelConntector(){
		return $this->modelConnect;
	}
	
	protected function getOverlayData(){
		$this->getOverlayColumn();
		$clause = $this->getRefreshClause();
		if(strlen($clause)) $this->select($this->overlayColumn, $clause);
		else $this->data = array();
	}
	
	protected function getOverlayColumn(){
		$this->overlayColumn = $this->modelConnector->getColumnNameByBoolean('isList');
	}
	
	protected function getRefreshClause(){
		$this->parentColumn = $this->modelConnector->getParentColumnName();
		if(strlen($this->parentColumn) == 0 and state_is_develop()){
			$pattern = tt('Model of %s has no parent column. Please set isParent of the appropriated column to be true.');
			$message = sprintf($pattern, $this->fullModuleName);
			notify_add_error($message);
		}
		$this->parentID = (int) gg('parent');
		$refreshID = explode(':', gg('refresh_id'));
		$clause = array();
		if($this->parentID){
			$clause[] = $this->parentColumn.'='.$this->parentID;
		}
		if(count($refreshID)){
			foreach($refreshID as $key => $value){
				$refreshID[$key] = (int) $value;
			}
			$clause[] = 'id='.join(' OR id=', $refreshID);
		}
		if(count($clause)) return 'WHERE '.join(' OR ', $clause).' ORDER BY id';
		else return null;
	}
	
	private function setAction(){
		$this->addAction($this->fullModuleName.'_overlay_write', 'overlayWrite');
		$this->addAction($this->fullModuleName.'_overlay_insert', 'overlayInsert');
		$this->addAction($this->fullModuleName.'_overlay_edit', 'overlayEdit');
		$this->addAction($this->fullModuleName.'_overlay_refresh', 'overlayRefresh');
	}
}
?>
