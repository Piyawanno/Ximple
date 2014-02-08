<?php
class CharColumn extends ModelColumn{
	function CharColumn($label, $help=null){
		$this->setType('char');
		$this->label = $label;
		$this->help = $help;
		$this->isAllowedTranslate = true;
		$this->setFormAttribute('size', 15);
		$this->setFormAttribute('maxlength', 80);
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$this->name;
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('id', $id);
		$this->setFormAttribute('value', $this->data);
		$this->setFormAttribute('class', 'char_input', true);
		$render = '<input '.$this->renderFormAttribute().'/>';
		$render.= '<span id="info_'.$id.'"></span>';
		return $render;
	}
	
	public function renderGridForm($formID){
		$this->setFormAttribute('name', $this->name.'[]');
		$this->setFormAttribute('value', $this->data);
		$this->setFormAttribute('class', 'grid_char_input', true);
		return '<input '.$this->renderFormAttribute().' />';
	}
}
?>
