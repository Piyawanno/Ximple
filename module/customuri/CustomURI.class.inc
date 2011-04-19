<?php
execute_add_class('customuri', 'CustomURI');
include('CustomURIModel.class.inc');

class CustomURI extends Control{
	private $existLabel;
	private $tooShortLabel;
	
	function CustomURI(){
		$this->moduleTitle = tt('CustomURI');
		$this->moduleName = 'customuri';
		$this->tableName = 'customuri';
		$this->setAdmin('customuri_admin');
		$this->addAction('customuri_check_mapped_exist', 'checkMappedExist');
		$this->init(new CustomURIModel());
		$this->existLabel = tt('The choosen mapped URI exists. Please select other URI.');
		$this->tooShortLabel = tt('The choosen mapped URI is too short.');
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		
	}
	
	public function write(){
		head_add_js_var('customURIUpdate', false);
		head_add_js_var('customURIExists', $this->existLabel);
		head_add_js_var('customURITooShort', $this->tooShortLabel);
		head_add_js('module/customuri/customuri.js');
		return Control::write();
	}
	
	public function edit(){
		head_add_js_var('customURIUpdate', true);
		head_add_js_var('customURIID', ((int) gg('id')));
		head_add_js_var('customURIExists', $this->existLabel);
		head_add_js_var('customURITooShort', $this->tooShortLabel);
		head_add_js('module/customuri/customuri.js');
		return Control::write();
	}
	
	public function insert(){
		if(!$this->checkMappedExist(pp('mapped_URI'))){
			Control::insert();
		}else{
			notify_add_error(tt('The given mapped URI exists.'));		
		}
	}
	
	public function update(){
		if(!$this->checkMappedExist(pp('mapped_URI'), pp('id'))){
			Control::update();
		}else{
			notify_add_error(tt('The given mapped URI exists.'));		
		}
	}
	
	public function ajaxCheckMappedExist(){
		execute_set_ajax();
		if($this->checkMappedExist(gg('mapped_URI'), (int) gg('URI_ID'))) return 'exist';
		else return 'not exist';
	}
	
	private function checkMappedExist($mappedURI, $updateID=0){
		if($updateID != 0){
			$clause = "WHERE mapped_URI='$mappedURI' and section=".SECTION;
		}else{
			$clause = "WHERE mapped_URI='$mappedURI' and section=".SECTION." AND id!=$updateID";
		}
		$this->select(array('id'), $clause);
		if(count($this->data)) return true;
		else return false;
	}
}
?>
