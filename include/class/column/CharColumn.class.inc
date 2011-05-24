<?php
class CharColumn extends ModelColumn{
	function CharColumn($label, $help=null){
		$this->setType('char');
		$this->label = $label;
		$this->help = $help;
	}
	
	public function enableTranslate(){
		$this->isTranslate = true;
	}
	
	public function renderForm($formID){
		$render = '<input name="'.$this->name.'" id="'.$formID.'" value="'.$this->data.'"/>';
		$render.= '<span id="info_'.$formID.'_'.$this->name.'"></span>';
		return $render;
	}
	
	public function renderGridForm($formID){
		return '<input name="'.$this->name.'[]" value="'.$this->data.'"/>';
	}
}
?>
