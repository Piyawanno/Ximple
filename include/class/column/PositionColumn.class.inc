<?php
require_once('CharColumn.class.inc');

class PositionColumn extends CharColumn{
	function PositionColumn($label, $help=null){
		CharColumn::CharColumn($label, $help);
		$this->defaultData = 0;
	}
	
	public function triggerGetJavaScript(){
		head_add_js('include/javascript/position.column.js');
	}
	
	public function renderForm($formID){
		head_add_css('position_column.css');
		$id = $formID.'_'.$this->name;
		if(empty($this->data)) $this->data = $this->defaultData;
		$renderArray = array(
			'form_id' => $id,
			'data' => $this->data,
		);
		$render = render($renderArray, 'position_column.tpl', 'position_column');
		
		$this->setFormAttribute('type', 'hidden');
		$render.= CharColumn::renderForm($formID);
		return $render;
	}
}
?>
