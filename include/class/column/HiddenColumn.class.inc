<?php
class HiddenColumn extends ModelColumn{
	function HiddenColumn($default, $type){
		$this->setType($type);
		$this->defaultData = $default;
		$this->data = $default;
	}
	
	public function renderForm($formID){
		$render = '<input name="'.$this->name.'" id="'.$formID.'" value="'.$this->data.'" type="hidden"/>';
		$render.= '<span id="info_'.$formID.'_'.$this->name.'"></span>';
		return $render;
	}
	
	public function renderGridForm($formID){
		return '<input name="'.$this->name.'[]" value="'.$this->data.'" type="hidden"/>';
	}
}
?>
