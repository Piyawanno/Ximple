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
			$this->setFormAtrribute('value', $value);
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
			$this->setFormAtrribute('checked', 'checked');
			$this->editable = '';
		}else{
			$this->setFormAtrribute('checked', '');
			$this->editable = 'disabled';
		}
	}
	
	private function setCheckBoxAttribute($relation){
		$this->resetFormAttribute();
		$this->setFormAtrribute('type', 'checkbox');
		$this->setFormAtrribute('name', 'check_'.$this->name.'[]');
		$this->setFormAtrribute('class', 'checkedit');
		$this->setFormAtrribute('rel', $relation);
		$this->setFormAtrribute('style', 'border:none;');
	}
	
	private function setInputAttribute($id, $data){
		$this->resetFormAttribute();
		$this->setFormAtrribute('id', $id);
		$this->setFormAtrribute('name', $this->name.'[]');
		$this->setFormAtrribute('disabled', $this->editable);
		$this->setFormAtrribute('value', $data);
		$this->setFormAtrribute('size', 25);
	}
}
?>
