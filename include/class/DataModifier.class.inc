<?php
class DataModifier{
	private $id;
	private $table;
	private $modelConnector;
	private $data;
	private $dataDB;
	private $columnDB;
	private $fileColumn;
	private $noneColumn;
	private $multipleInsertColumn;

	function DataModifier($table, $modelConnector){
		$this->table = $table;
		$this->modelConnector = $modelConnector;
	}
	
	public function getID(){
		return $this->id;
	}
	
	public function prepareInsert(){
		$this->modelConnector->triggerPreInsert();
		$this->getColumn();
		$this->prepare();
		$this->modelConnector->triggerPostInsert();
	}
	
	public function insert($isCaptcha){
		if(!$isCaptcha or $this->checkCaptcha()){
			$this->getMultipleInsertColumn();
			if(count($this->multipleInsertColumn))  return $this->insertMultipleRows();
			else return $this->insertSingleRow();
		}
		return false;
	}
	
	public function prepareUpdate(){
		$this->modelConnector->triggerPreUpdate();
		$this->getColumn();
		$this->dataDB = $this->modelConnector->getColumnAttribute('data');
		$this->dropOldFile(false);
		$this->prepare();
		$this->modelConnector->triggerPostUpdate();
	}
	
	public function update($isCaptcha){
		if(!$isCaptcha or $this->checkCaptcha()){
			$this->getMultipleInsertColumn();
			if(count($this->multipleInsertColumn)) return $this->updateMultipleRows();
			else return $this->updateSingleRow();
		}
		return false;
	}
	
	public function prepareDrop(){
		$this->modelConnector->triggerDrop();
		$this->getColumn();
		$this->dataDB = $this->modelConnector->getColumnAttribute('data');
		$this->dropOldFile(true);
	}
	
	public function drop(){
		$this->checkID();
		db_drop($this->table, $this->id);
	}
	
	private function getColumn(){
		$this->columnDB = $this->modelConnector->getColumnNameByBoolean('isDB');
		$fileColumn = $this->modelConnector->getColumnNameByAttribute('form', 'file');
		$fileColumn = array_intersect($fileColumn, $this->columnDB);
		$muliFilesColumn = $this->modelConnector->getColumnNameByAttribute('form', 'multiplefiles');
		$muliFilesColumn = array_intersect($muliFilesColumn, $this->columnDB);
		$this->fileColumn = array_merge($fileColumn, $muliFilesColumn);
		$this->noneColumn = $this->modelConnector->getColumnNameByAttribute('form', 'none');
	}
	
	private function prepare(){
		$this->getData();
		$this->checkNull();
		$this->formatCalendar();
		$this->uploadFile();
		$this->serializeData();
		$this->checkTag();
		$this->modelConnector->setData($this->data);
	}
	
	private function getData(){
		$type = $this->modelConnector->getPHPType();
		foreach($this->columnDB as $name){
			if(in_array($name, $this->noneColumn)){
				$data = $this->modelConnector->getAttribute($name, 'defaultData');
			}else{
				$data = pp($name);
			}
			if($data === null and $type[$name] != 'array' and !in_array($name, $this->fileColumn) and state_is_develop()){
				$message  = 'Data in column : '.$name.' is not set. ';
				$message .= 'Please check model and form-rendering.';
				notify_add_error($message);
			}
			settype($data, $type[$name]);
			$this->data[$name] = $data;
		}
	}
	
	private function checkNull(){
		$columnName = $this->modelConnector->getColumnNameByBoolean('isNotNull');
		$columnName = array_intersect($columnName, $this->columnDB);
		$label = $this->modelConnector->getColumnAttribute('label');
		foreach($columnName as $name){
			if(empty($this->data[$name]) and !in_array($name, $this->fileColumn)){
				$p = tt('Data in column %s is not allowed be empty.');
				error_syslog(sprintf($p, $label[$name]));
			}
		}
	}
	
	private function formatCalendar(){
		$columnName = $this->modelConnector->getColumnNameByAttribute('type', 'timestamp');
		$columnName = array_intersect($columnName, $this->columnDB);
		foreach($columnName as $name){
			$this->data[$name] = date('Y-m-d H:i:s', strtotime($this->data[$name]));
		}
	}
	
	private function uploadFile(){
		include_once(ROOT_PATH.'include/tool/image.tool.inc');
		$path = $this->modelConnector->getColumnAttribute('path');
		$isImage = $this->modelConnector->getColumnNameByBoolean('isImage');
		$maxWidth = $this->modelConnector->getColumnAttribute('maxWidth');
		foreach($this->fileColumn as $name){
			$image = in_array($name, $isImage);
			$fileName = io_upload(ff($name), $path[$name], $image);
			if($image and $fileName){
				$imagePath = ROOT_PATH.$fileName;
				image_check_max_width(ff($name), $imagePath, $maxWidth[$name]);
			}
			if($fileName) $this->data[$name] = $fileName;
			else $this->data[$name] = $this->dataDB[$name];
		}
	}
	
	private function dropOldFile($checkInput=false){
		foreach($this->fileColumn as $name){
			$file = ff($name);
			if(((isset($file['size']) and $file['size']) or $checkInput) and !empty($this->dataDB[$name])){
				if(is_file(ROOT_PATH.$this->dataDB[$name])){
					io_drop_file(ROOT_PATH.$this->dataDB[$name]);
				}
			}
		}
	}
	
	private function serializeData(){
		$columnName = $this->modelConnector->getColumnNameByBoolean('isSerialize');
		$columnName = array_intersect($columnName, $this->columnDB);
		foreach($columnName as $name){
			if(!empty($this->data[$name])){
				$this->data[$name] = serialize($this->data[$name]);
			}else{
				$this->data[$name] = serialize(array());
			}
		}
	}
	
	private function checkID(){
		$this->id = (int) gg('id');
		if(empty($this->id)){
			error_syslog(tt('Data can not be modified without any given ID.'));
		}
	}
	
	private function checkTag(){
		$columnName = $this->modelConnector->getColumnNameByAttribute('isAllTags', false);
		$columnName = array_intersect($columnName, $this->columnDB);
		$type = $this->modelConnector->getPHPType();
		$allowed_tag = cc('allowed_tags');
		foreach($columnName as $name){
			if($type[$name] == 'string'){
				$this->data[$name] = strip_tags($this->data[$name], $allowed_tag);
			}
		}
	}
	
	private function checkCaptcha(){
		if(authority_is_guest()){
			include_once(ROOT_PATH.'include/tool/captcha.tool.inc');
			$gentime = pp('captcha_gentime_captcha');
			$parity = pp('captcha_code_captcha');
			$code = pp('captcha');
			if(!captcha_check($gentime, $code, $parity)){
				notify_add_error(tt('Your given code from the image was wrong. Data is not inserted.'));
				return false;
			}
		}
		return true;
	}
	
	private function getDataFromConnector(){
		$this->data = $this->modelConnector->getColumnAttribute('data');
		foreach($this->data as $key => $value){
			if(!in_array($key, $this->columnDB)) unset($this->data[$key]);
		}
	}
	
	private function getMultipleInsertColumn(){
		$this->multipleInsertColumn = $this->modelConnector->getColumnNameByBoolean('isMultipleInsert');
	}
	
	private function insertSingleRow(){
		$this->getDataFromConnector();
		$this->id = db_insert($this->table, $this->data);
		return true;
	}
	
	private function insertMultipleRows(){
		$this->getDataFromConnector();
		if($this->checkDataSymmetry()){
			$this->formatMultipleData();
			$this->id = array();
			foreach($this->data as $key => $value){
				$this->id[] = db_insert($this->table, $value);
			}
			return true;
		}else{
			return false;
		}
	}
	
	private function updateSingleRow(){
		$this->checkID();
		$this->getDataFromConnector();
		db_update($this->table, $this->data, $this->id);
		return true;
	}
	
	private function updateMultipleRows(){
		
	}
	
	private function checkDataSymmetry(){
		$newCount = -1;
		$errorMessage = '';
		foreach($this->multipleInsertColumn as $columnName){
			if(!is_array($this->data[$columnName])){
				$errorMessage = 'Data should be array : '.$columnName;
				break;
			}
			$oldCount = $newCount;
			$newCount = count($this->data[$columnName]);
			if($newCount != $oldCount and $oldCount != -1){
				$errorMessage = 'Data are not symmetry : '.$columnName;
				break;
			}
		}
		if(strlen($errorMessage)){
			if(state_is_develop()) notify_add_error($errorMessage);
			return false;
		}else{
			return true;
		}
	}
	
	private function formatMultipleData(){
		$formattedData = array();
		$n = count($this->data[$this->multipleInsertColumn[0]]);
		for($i=0; $i< $n; $i++){
			foreach($this->data as $key => $value){
				if(in_array($key, $this->multipleInsertColumn)){
					$formattedData[$i][$key] = $value[$i];
				}else{
					$formattedData[$i][$key] = $value;
				}
			}
		}
		$this->data = $formattedData;
	}
}
?>
