<?php

class ModelConnector{
	private $id;
	private $parentID;
	private $modelObject;
	private $model;
	private $cacheName = array();
	private $cacheAttribute = array();
	
	function ModelConnector($model, $modelObject){
		$this->model = $model;
		$this->modelObject = $modelObject;
	}
	
	public function setID($id){
		$this->id = $id;
		$this->triggerGetID();
	}
	
	public function setParentID($parentID){
		$this->parentID = $parentID;
	}
	
	public function getColumn($col){
		if(isset($this->model[$col])){
			return $this->model[$col];
		}
	}
	
	public function getColumnName(){
		$col = array('id');
		foreach($this->model as $key => $value){
			if($value->isDB) $col[] = $key;
		}
		return $col;
	}
	
	public function getColumnNameExcepted($excepted){
		$col = $this->getColumnName();
		foreach($col as $key => $value){
			if(in_array($value, $excepted)) unset($col[$key]);
		}
		return $col;
	}
	
	public function getFormColumn(){
		$model = $this->model;
		foreach($model as $key => $value){
			if(!$value->isForm){
				unset($model[$key]);
			}
		}
		return $model;
	}
	
	public function getTranslateFormColumn(){
		$model = $this->model;
		foreach($model as $key => $value){
			if(!$value->isTranslate){
				unset($model[$key]);
			}
		}
		return $model;
	}
	
	public function setAsConfigForm($col){
		if($this->model[$col]->form != 'hidden'){
			$this->model[$col]->isForm = false;
		}
	}
	
	public function getColumnAttribute($attrName){
		$attr = array();
		foreach($this->model as $key => $value){
			$attr[$key] = $value->$attrName;
		}
		return $attr;
	}
	
	public function resetData(){
		$model = $this->model;
		foreach($model as $key => $value){
			if(!isset($model[$key]->defaultData)){
				$model[$key]->data = '';
			}else{
				$model[$key]->data = $model[$key]->defaultData;
			}
		}
		return $model;
	}
	
	public function addModel($name, $model){
		$this->model[$name] = $model;
	}
	
	public function setData($data){
		$model = $this->model;
		foreach($model as $key => $value){
			if(isset($data[$key])){
				if($model[$key]->isUpdateTime) $model[$key]->data = NOW;
				else $model[$key]->data = $data[$key];
			}
		}
		return $model;
	}
	
	public function setAttribute($columnName, $attributeName, $attributeValue){
		$this->model[$columnName]->$attributeName = $attributeValue;
	}
	
	public function getAttribute($columnName, $attributeName){
		return $this->model[$columnName]->$attributeName;
	}
	
	public function getColumnNameByBoolean($attrName){
		return $this->getColumnNameByAttribute($attrName, true);
	}
	
	public function getColumnNameByAttribute($attrName, $attr){
		if(isset($this->cacheName[$attrName][$attr])){
			return $this->cacheName[$attrName][$attr];
		}
		
		$column = array();
		foreach($this->model as $key => $value){
			if($value->$attrName == $attr) $column[] = $key;
		}
		$this->cacheName[$attrName][$attr] = $column;
		return $column;
	}
	
	public function getPHPType(){
		$type = array();
		foreach($this->model as $key => $modelColumn){
			$type[$key] = $modelColumn->getPHPType();
		}
		return $type;
	}
	
	public function triggerPreInsert(){
		$this->trigger('PreInsert');
	}
	
	public function triggerPreUpdate(){
		$this->trigger('PreUpdate');
	}
	
	public function triggerPostInsert(){
		$this->trigger('PostInsert');
	}
	
	public function triggerPostUpdate(){
		$this->trigger('PostUpdate');
	}
	
	public function triggerPostDBInsert(){
		$this->trigger('PostDBInsert');
	}
	
	public function triggerPostDBUpdate(){
		$this->trigger('PostDBUpdate');
	}
	
	public function triggerDrop(){
		$this->trigger('Drop');
	}
	
	public function triggerPostDBDrop(){
		$this->trigger('PostDBDrop');
	}
	
	public function triggerInsertForm(){
		$this->trigger('InsertForm');
	}
	
	public function triggerUpdateForm(){
		$this->trigger('UpdateForm');
	}
	
	public function triggerSetParent(){
		$this->triggerSingleParameter('SetParent', $this->parentID);
	}
	
	public function triggerGetID(){
		$this->triggerSingleParameter('GetID', $this->id);
	}
	
	public function triggerSelect($data){
		if(method_exists($this->modelObject, 'triggerSelect')){
			$this->modelObject->triggerSelect($data);
		}
		$triggerColumn = array();
		foreach($this->model as $key => $value){
			$methodName = 'triggerSelect';
			if(method_exists($value, $methodName)) $triggerColumn[] = $key;
		}
		if(count($triggerColumn)){
			foreach($data as $id => $value){
				foreach($triggerColumn as $key => $col){
					if(isset($this->model[$col]) and isset($value[$col])){
						$this->model[$col]->data = $value[$col];
						$this->model[$col]->triggerSelect();
						$data[$id][$col] = $this->model[$col]->data;
					}
				}
			}
		}
		return $data;
	}
	
	public function initCaptchaColumn(){
		if(authority_is_guest()){
			$captchaCode = new ModelColumn();
			$captchaCode->form = 'captcha';
			$captchaCode->type = 'char';
			$captchaCode->isDB = false;
			$captchaCode->isNotNull = true;
			$captchaCode->label = tt('insert code from followed picture before submit');
			$additionalModel = array();
			$additionalModel['captcha'] = $captchaCode;
			$this->model = array_merge($additionalModel, $this->model);
		}
	}
	
	public function checkExist($col){
		return isset($this->model[$col]);
	}
	
	public function hasTranslate(){
		$model = $this->getTranslateFormColumn();
		return (count($model) and is_array(cc('supported_language')));
	}
	
	private function trigger($event){
		$methodName = 'trigger'.$event;
		if(method_exists($this->modelObject, $methodName)){
			$this->modelObject->$methodName();
		}
		foreach($this->model as $key => $value){
			if(method_exists($value, $methodName)){
				$value->$methodName();
			}
		}
	}
	
	private function triggerSingleParameter($event, $parammeter){
		$methodName = 'trigger'.$event;
		if(method_exists($this->modelObject, $methodName)){
			$this->modelObject->$methodName($parammeter);
		}
		foreach($this->model as $key => $value){
			if(method_exists($value, $methodName)){
				$value->$methodName($parammeter);
			}
		}
	}
}
?>
