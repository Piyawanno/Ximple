<?php
class DataModifier{
	private $id;
	private $table;
	private $modelConnector;
	private $data;
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
		$this->columnDB = $this->modelConnector->getColumnNameByBoolean('isDB');
		$this->prepare();
		$this->modelConnector->triggerPostInsert();
		$this->modelConnector->triggerCheckNull();
	}
	
	public function insert($isCaptcha){
		$retult = false;
		$this->data = $this->modelConnector->getData();
		if(!$isCaptcha or $this->checkCaptcha()){
			$this->getMultipleInsertColumn();
			if(count($this->multipleInsertColumn)){
				$retult = $this->insertMultipleRows();
			}else{
				$retult = $this->insertSingleRow();
			}
			$this->modelConnector->triggerPostDBInsert();
			extension_execute('insert', array($this->id, $this->table));
		}
		return $retult;
	}
	
	public function prepareUpdate($data=null, $id=null){
		$this->modelConnector->setDataDB($data);
		$this->checkID($id);
		$this->modelConnector->setID($this->id);
		$this->modelConnector->triggerPreUpdate();
		$this->columnDB = $this->modelConnector->getColumnNameByBoolean('isDB');
		$this->prepare();
		$this->modelConnector->triggerPostUpdate();
		$this->modelConnector->triggerCheckNull();
	}
	
	public function update($isCaptcha){
		$retult = false;
		if(!$isCaptcha or $this->checkCaptcha()){
			$this->getMultipleInsertColumn();
			if(count($this->multipleInsertColumn)){
				$retult = $this->updateMultipleRows();
			}else{
				$retult = $this->updateSingleRow();
			}
			$this->modelConnector->triggerPostDBUpdate();
			extension_execute('update', array($this->id, $this->table));
		}
		return $retult;
	}
	
	public function prepareDrop($id){
		$this->columnDB = $this->modelConnector->getColumnNameByBoolean('isDB');
		$this->checkID($id);
		$this->modelConnector->setID($this->id);
		$this->modelConnector->triggerDrop();
	}
	
	public function drop(){
		db_drop($this->table, $this->id);
		$this->modelConnector->setID($this->id);
		$this->modelConnector->triggerPostDBDrop();
		extension_execute('drop', array($this->id, $this->table));
	}
	
	public function checkCaptcha(){
		if(authority_is_guest()){
			include_once(INCLUDE_PATH.'tool/captcha.tool.inc');
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
	
	private function prepare(){
		$this->getData();
		$this->modelConnector->setData($this->data);
		$this->modelConnector->triggerSerialize();
		$this->modelConnector->triggerStripTag();
		$this->data = $this->modelConnector->getData();
	}
	
	private function getData(){
		$type = $this->modelConnector->getPHPType();
		foreach($this->columnDB as $name){
			$data = pp($name);
			settype($data, $type[$name]);
			$this->data[$name] = $data;
		}
	}
	
	private function checkID($id){
		if(empty($id)) $this->id = (int) gg('id');
		else $this->id = $id;
		if(empty($this->id)){
			error_syslog(tt('Data can not be modified without any given ID.'));
		}
	}
	
	private function getDataFromConnector(){
		$this->data = $this->modelConnector->getData();
		foreach($this->data as $key => $value){
			if(!in_array($key, $this->columnDB)) unset($this->data[$key]);
		}
	}
	
	private function getMultipleInsertColumn(){
		$this->multipleInsertColumn = $this->modelConnector->getColumnNameByBoolean('isMultipleInsert');
		$this->multipleInsertColumn = array_intersect($this->multipleInsertColumn, $this->columnDB);
	}
	
	private function insertSingleRow(){
		$this->getDataFromConnector();
		$this->id = db_insert($this->table, $this->data);
		$this->modelConnector->setID($this->id);
		return true;
	}
	
	private function insertMultipleRows(){
		$this->getDataFromConnector();
		$this->formatMultipleData();
		$this->id = array();
		foreach($this->data as $key => $value){
			$this->modelConnector->setData($value);
			$this->modelConnector->triggerCheckNull();
			if($this->checkNotNull()){
				$this->id[] = db_insert($this->table, $value);
			}
		}
		return true;
	}
	
	private function updateSingleRow(){
		$this->getDataFromConnector();
		db_update($this->table, $this->data, $this->id);
		return true;
	}
	
	private function updateMultipleRows(){
		$this->getDataFromConnector();
		$this->formatMultipleData();
		if(!is_array($this->id)) $this->id = array();
		foreach($this->data as $key => $value){
			$this->modelConnector->setData($value);
			$this->modelConnector->triggerCheckNull();
			if($this->checkNotNull()){
				$this->id[] = $key;
				db_update($this->table, $value, $key);
			}else{
				db_drop($this->table, $key);
			}
		}
		return true;
	}
	
	private function formatMultipleData(){
		$formattedData = array();
		$dataKey = array_keys($this->data[$this->multipleInsertColumn[0]]);
		foreach($dataKey as $i){
			foreach($this->data as $key => $value){
				if(is_array($value)){
					$formattedData[$i][$key] = $value[$i];
				}else{
					$formattedData[$i][$key] = $value;
				}
			}
		}
		$this->data = $formattedData;
	}
	
	private function checkNotNull(){
		$isNotNullColumn = $this->modelConnector->getColumnNameByBoolean('isNotNull');
		foreach($isNotNullColumn as $key => $value){
			$column = $this->modelConnector->getColumn($value);
			if(!$column->triggerCheckNull()) return false;
		}
		return true;
	}
}
?>
