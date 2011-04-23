<?php
class ContentStatusColumn extends ModelColumn{
	private $moduleName;
	private $status;
	
	public $isTriggerSelect = false;
	
	function ContentStatusColumn($label, $moduleName){
		$this->label = $label;
		$this->form = 'radio';
		$this->type = 'int';
		$this->moduleName = $moduleName;
	}
	
	function setStatus($status){
		$this->status = $status;
		$this->defaultData = cc($this->moduleName.'_'.$this->status.'_default');
	}
	
	function setOption($option){
		$this->option = $option;
	}
	
	public function triggerInsertForm(){
		$this->initSelect();
	}
	
	public function triggerUpdateForm(){
		$this->initSelect();
	}
	
	public function triggerSelect(){
		if($this->isTriggerSelect) $this->data = $this->option[$this->data];
	}
	
	private function initSelect(){
		$adminGroup = $this->moduleName.'_admin';
		$editorGroup = $this->moduleName.'_editor';
		if(!(authority_group($adminGroup) or authority_group($editorGroup))){
			$config = cc($this->moduleName.'_'.$this->status);
			$option = array();
			foreach($config as $key){
				$option[$key] = $this->option[$key];
			}
			$this->option = $option;
		}
	}
}
?>
