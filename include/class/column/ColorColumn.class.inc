<?php
class ColorColumn extends CharColumn{
	function ColorColumn($label, $help=null){
		CharColumn::CharColumn($label, $help);
		$this->defaultData = "#5555ee";
		$this->data = "#5555ee";
	}
	
	public function renderForm($formID){
		head_add_css('include/external/farbtastic/farbtastic.css');
		head_add_js('include/external/farbtastic/farbtastic.js');
		head_add_js('include/javascript/colorcolumn.js');
		head_add_js_var('selectColorLabel', tt('Select Color'));
		
		$this->setFormAttribute('class', 'color_picker');
		$id = $form_id.'_'.$name;
		$render  = '<div id="picker_'.$id.'"></div>';
		$render .= CharColumn::renderForm($formID);
		$render .= '<span id="info_'.$id.'"></span>';
		return $out;
	}
}
?>
