<?php
class CharColumn extends ModelColumn{
	function CharColumn($label, $help=null){
		$this->setType('char');
		$this->label = $label;
		$this->help = $help;
		$this->isAllowedTranslate = true;
		$this->setFormAtrribute('size', 25);
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$this->name;
		$this->setFormAtrribute('name', $this->name);
		$this->setFormAtrribute('id', $id);
		$this->setFormAtrribute('value', $this->data);
		$render = '<input '.$this->renderFormAttribute().'/>';
		$render.= '<span id="info_'.$id.'"></span>';
		return $render;
	}
	
	public function renderGridForm($formID){
		$this->setFormAtrribute('name', $this->name.'[]');
		$this->setFormAtrribute('value', $this->data);
		return '<input '.$this->renderFormAttribute().'/>';
	}
}
?>
