<?php
require_once('SelectiveColumn.class.inc');
class CheckBoxColumn extends SelectiveColumn{
	private $editable;
	
	function CheckBoxColumn($label, $option, $help=null){
		SelectiveColumn::SelectiveColumn($label, $option, $help);
		$this->setType('array');
	}
	
	protected function renderForm($formID){
		head_add_js('include/javascript/checkeditcolumn.js');
		$id = $formID.'_'.$name;
		$this->checkSortable();
		$render = '<div class="checkedit_list">';
		$render.= '<ul class="'.$this->listClass.'" id="'.$id.'">';
		$i = 0;
		foreach($modelCol->option as $key => $value){
			$this->setFormAttribute('value', $value);
			$this->getCheck($key);
			$render .= '<li>'.$this->imageTag;
			$this->setCheckBoxAttribute($id.$i);
			$render .= '<input '.$this->renderFormAttribute().'/>';
			$this->setInputAttribute($id.$i, $value);
			$render .= '<input '.$this->renderFormAttribute().'/>';
			$render .= '</li>'
			$i++;
		}
		$render .= '</ul>';
		$render .= '</div>';
		$render .= '<span id="info_'.$id.'"></span>';
		$render .= '<p style="clear:both;">';
		return $render;
	}
	
	private function getCheck($data){
		if(is_array($this->data) and in_array($data, $this->data)){
			$this->setFormAttribute('checked', 'checked');
			$this->editable = '';
		}else{
			$this->setFormAttribute('checked', '');
			$this->editable = 'disabled';
		}
	}
	
	private function setCheckBoxAttribute($relation){
		$this->resetFormAttribute();
		$this->setFormAttribute('type', 'checkbox');
		$this->setFormAttribute('name', 'check_'.$this->name.'[]');
		$this->setFormAttribute('class', 'checkedit');
		$this->setFormAttribute('rel', $relation);
		$this->setFormAttribute('style', 'border:none;');
	}
	
	private function setInputAttribute($id, $data){
		$this->resetFormAttribute();
		$this->setFormAttribute('id', $id);
		$this->setFormAttribute('name', $this->name.'[]');
		$this->setFormAttribute('disabled', $this->editable);
		$this->setFormAttribute('value', $data);
		$this->setFormAttribute('size', 25);
	}
}
?>
