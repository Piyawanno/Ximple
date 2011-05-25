<?php
require_once('SelectiveColumn.class.inc');
class SelectColumn extends SelectiveColumn{
	public function renderForm($formID){
		$this->setFormAtrribute('name', $this->name);
		$render = $this->renderSelectForm($formID);
		$render .= '<span id="info_'.$id.'"></span>';
		return $render;
	}
	
	public function renderGridForm($formID){
		$this->setFormAtrribute('name', $this->name.'[]');
		return $this->renderSelectForm($formID);
	}
	
	private function renderSelectForm($formID){
		$id = $formID.'_'.$this->name;
		$this->setFormAtrribute('id', $id);
		$render = '<select '.$this->renderFormAttribute().'/>';
		foreach($this->option as $key => $value){
			$selected = $this->data == $key ? 'selected="selected"' : '';
			$render .= '<option value="'.$key.'" '.$selected.'>'.$value.'</option>';
		}
		$render .= '</select>';
		return $render;
	}
}
?>