<?php
include_once(ROOT_PATH.'include/class/Control.class.inc');
include('AdvertiseModel.class.inc');

class Advertise extends Control{
	function Advertise(){
		$this->moduleTitle = tt('Advertise');
		$this->moduleName = 'advertise';
		$this->tableName = 'advertise';
		$this->setAdmin('advertise_admin');
		$this->addAccessMethod('guest', 'redirect');
		$this->init(new AdvertiseModel());
		document_set_path($this->moduleTitle, 'advertise_list');
	}
	
	public function index(){
		if(MODE_ID) return $this->showDetail();
		else return $this->listPage();
	}
	
	public function showDetail(){
		$this->id = (int) gg('id');
		$this->selectByID($this->column);
		document_set_path($this->dataByID['name']);
		return render($this->dataByID, 'advertise.tpl', 'advertise');
	}
	
	public function renderBanner(){
		head_add_css('advertise.css');
		$clause = 'WHERE position='.gg('id').' AND section='.SECTION;
		$this->select(array('id', 'banner', 'uri', 'name'), $clause);
		return render(array('data' => $this->data), 'banner.tpl', 'banner');
	}
	
	public function listPage(){
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrderDesc = 'id';
		$this->listMeta->mode = $this->moduleName;
		$this->setListWriteIcon(tt('Add new Advertise'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		$this->selectListPage(20);
		return $this->renderListPage();
	}
	
	public function redirect(){
		$this->id = gg('id');
		$this->selectByID(array('id', 'uri', 'name'));
		count_increase('advertise', $this->id);
		header('Location: '.$this->dataByID['uri']);
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('advertise/'.$this->id);
	}
	
	public function update(){
		Control::update();
		document_set_redirect('advertise/'.$this->id);
	}
}
?>