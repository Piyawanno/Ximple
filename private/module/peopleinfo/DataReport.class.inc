<?php
execute_add_extended_class('peopleinfo', 'report', 'DataReport');

include_once(INCLUDE_PATH.'class/ConfigControl.class.inc');
include_once('DataReportModel.class.inc');

class DataReport extends ConfigControl{
	function DataReport(){
		$this->moduleName = 'peopleinfo';
		$this->moduleExtension = 'report';
		$this->moduleTitle = tt('People Information Center Report');
		$this->setAdmin('peopleinfo_admin');
		$this->init(new DataReportModel());
	}
	
	public function index(){
		document_set_path(tt('People'), 'peopleinfo');
		$this->formMeta->mode = 'peopleinfo_report';
		$this->formMeta->title = $this->moduleTitle;
		$render = $this->render();
		if(is_array(pp('shown_type'))){
			$render .= $this->renderReport();
		}
		return $render;
	}
	
	private function renderReport(){
		head_add_css('list.css');
		$configType = cc('peopleinfo_data_type');
		$type = array();
		$data = $this->getPeopleData();
		foreach(pp('shown_type') as $key => $value){
			$type[$value] = $configType[$value];
		}
		$renderArray = array(
			'data_type' => $type,
			'data' => $data,
			'csv' => $this->saveCSV($data, $type),
			'label' => $this->getLabel(),
		);
		return render($renderArray, 'peopleinfo_report.tpl', 'peopleinfo_report');
	}
	
	private function getPeopleData(){
		$peopleID = $this->getPeopleID();
		if(count($peopleID) and count(pp('shown_type'))){
			$clause = 'WHERE id='.join(' OR id=', $peopleID);
			$people = db_select_single_column('people', 'name', $clause);
			$clause = 'WHERE (people='.join(' OR people=', $peopleID).') AND ';
			$clause.= '(data_type='.join(' OR data_type=', pp('shown_type')).')';
			$column = array('people', 'data_type', 'data');
			$data = db_select('people_data', $column, $clause);
			$peopleData = array();
			foreach($data as $key => $value){
				$peopleData[$value['people']]['data'][$value['data_type']] = $value['data'];
			}
			foreach($peopleData as $key => $value){
				$peopleData[$key]['name'] = $people[$key];
			}
			return $peopleData;
		}
		return array();
	}
	
	private function getPeopleID(){
		$clause = array();
		if(count(pp('data'))) $clause = $this->getClause();
		if(pp('and_or') == 'or'){
			$clause = 'WHERE '.join(' OR ', $clause);
			$data = db_select_single_column('people_data', 'people', $clause);
		}else{
			foreach($clause as $key => $value){
				$value = 'WHERE '.$value;
				if($key == 0){
					$data = db_select_single_column('people_data', 'people', $value);
				}else{
					$current = db_select_single_column('people_data', 'people', $value);
					$data = array_intersect($data, $current);
				}
			}
		}
		return $data;
	}
	
	private function getClause(){
		$condition = pp('condition');
		$type = pp('data_type');
		$data = pp('data');
		$numberCondition = array('>=', '>', '<', '<=');
		$itemClause = array();
		foreach($data as $key => $value){
			if(strlen($value)){
				if(in_array($condition[$key], $numberCondition)){
					$valueClause = 'CAST(data AS DECIMAL) '.$condition[$key].((double)$value);
				}else{
					$valueClause = 'data '.$condition[$key]." '$value'";
				}
				$itemClause[] = "($valueClause AND data_type=$type[$key])";
			}
		}
		return $itemClause;
	}
	
	private function saveCSV($data, $type){
		$csv = tt('name').', '.join(', ', $type)."\n";
		foreach($data as $id => $item){
			$row = array($item['name']);
			foreach($type as $key => $value){
				if(isset($item['data'][$key])) $row[] = $item['data'][$key];
				else $row[] = null;
			}
			$csv .= join(',', $row)."\n";
		}
		$name = md5(serialize(pp()));
		$directory = $this->createDirectory();
		io_write_file($directory.$name.'.csv', $csv);
		return $name.'.csv';
	}
	
	private function createDirectory(){
		$directory = FILES_PATH.'peopleinfo/';
		if(!is_dir($directory)) mkdir($directory);
		$directory.= 'csv/';
		if(!is_dir($directory)) mkdir($directory);
		return $directory;
	}
	
	private function getLabel(){
		$configType = cc('peopleinfo_data_type');
		$type = pp('data_type');
		$data = pp('data');
		$condition = pp('condition');
		$label = array();
		foreach($data as $key => $value){
			if(strlen($value)){
				$label[] = $configType[$type[$key]].$condition[$key].$value;
			}
		}
		return join(' '.pp('and_or').' ', $label);
	}
}
?>
