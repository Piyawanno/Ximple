<?php
abstract class SelectiveColumn extends ModelColumn{
	public $option;
	public $isSortable;
	
	protected $listClass;
	protected $divisionClass;
	protected $imageTag;
	
	function SelectiveColumn($label, $option, $help=null){
		$this->setType('char');
		$this->label = $label;
		$this->help = $help;
		$this->option = $option;
	}
	
	public function check(){
		if(!is_array($this->option) and state_is_develop()){
			notify_add_error('Option of '.$this->name.' is not set.');
		}
	}
	
	public function triggerSelect(){
		if(!is_array($this->data)){
			$this->data = $this->option[$this->data];
		}
	}
	
	protected function renderRawsForm($formID){
		$id = $formID.'_'.$name;
		$render = '<div class="'.$this->divisionClass.'">';
		$render.= '<ul class="'.$this->listClass.'" id="'.$id.'">';
		$this->setFormAtrribute('style', 'border:none;');
		foreach($modelCol->option as $key => $value){
			$this->setFormAtrribute('value', $value);
			$this->getCheck($key);
			$render .= '<li>'.$this->imageTag;
			$render .= '<input '.$this->renderFormAttribute().'/>'.$value;
			$render .= '</li>';
		}
		$render .= '</ul>';
		$render .= '</div>';
		$render .= '<span id="info_'.$id.'"></span>';
		$render .= '<p style="clear:both;">';
		return $render;
	}
	
	protected function getCheck($data){
	}
	
	protected function checkSortable(){
		if($this->isSortable){
			$this->listClass = 'sortable_form';
			$this->imageTag = '<img src="'.ROOT_URI.'files/icon/move.png" />';
			head_add_js('include/javascript/sortable.js');
		}else{
			$this->listClass = 'unsortable_form';
			$this->imageTag = '';
		}
	}
}
?>
