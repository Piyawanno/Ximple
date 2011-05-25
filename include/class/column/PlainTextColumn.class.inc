<?php
class PlainTextColumn extends ModelColumn{
	function PlainTextColumn($label, $help=null){
		$this->setType('shorttext');
		$this->label = $label;
		$this->help = $help;
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$name;
		$this->setFormAtrribute('name', $this->name);
		$this->setFormAtrribute('id', $this->id);
		$this->setFormAtrribute('style', 'width:100%;height:120px;');
		$this->setFormAtrribute('rows', 20);
		$this->setFormAtrribute('class', 'plaintext');
		$render = '<textarea '.$this->renderFormAttribute().'>'.$this->data.'</textarea>';
		$render.= '<span id="info_'.$id.'"></span>';
		return $render;
	}
}
?>
