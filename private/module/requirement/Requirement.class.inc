<?php
execute_add_class('requirement', 'Requirement');
require_once('RequirementModel.class.inc');
require_once('requirement.tool.inc');

class Requirement extends Control{
	function Requirement(){
		$this->moduleName = 'requirement';
		$this->moduleTitle = tt('Requirement Sheet');
		$this->tableName = 'requirement';
		$this->init(new RequirementModel());
		$this->formMeta->isCaptcha = true;
		$this->setConfig();
		$this->setAccess();
		$this->setAction();
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		$this->id = (int) gg('id');
		if($this->id){
			$this->selectByID($this->column);
			document_set_path($this->dataByID['customer_name']);
			$this->dataByID['expectation_option'] = requirement_get_expectation_option();
			$this->dataByID['get_date'] = date(cc('time_format'), strtotime($this->dataByID['get_date']));
			return render($this->dataByID, 'requirement.tpl', 'requirement');
		}else{
			return $this->listPage();
		}
	}
	
	public function dropMenu(){
		db_drop('requirement_menu', (int) gg('id'));
	}
	
	public function dropFile(){
		db_drop('requirement_file', (int) gg('id'));
	}
	
	public function dropLink(){
		db_drop('requirement_link', (int) gg('id'));
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('');	
	}
	
	private function setConfig(){
		$tab = $this->getNewConfigForm(tt('About Tab Menu'));
		$description = tt('Tab Menu should categorize your web-site. ');
		$description.= tt('It should describe your web-pages.');
		$tab->setDescription($description);
		$tab->append('tab_menu');
		
		$design = $this->getNewConfigForm(tt('About Design'));
		$design->append('representation');
		$design->append('expectation');
		$design->append('file');
		$design->append('link');
	}
	
	private function setAccess(){
		$this->setAdmin('requirement_admin');
		$this->addAccessMethod('guest', 'write');
		$this->addAccessMethod('guest', 'insert');
	}
	
	private function setAction(){
		$this->addAction('requirement_drop_menu', 'dropMenu');
		$this->addAction('requirement_drop_file', 'dropFile');
		$this->addAction('requirement_drop_link', 'dropLink');
	}
}
?>
