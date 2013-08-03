<?php
require_once('SelectiveColumn.class.inc');
class RadioColumn extends SelectiveColumn{
	private $fillable = false;
	
	function RadioColumn($label, $option, $help=null){
		SelectiveColumn::SelectiveColumn($label, $option, $help);
	}
	
	public function renderForm($formID){
		$this->listClass = 'radio_list';
		$this->setFormAttribute('type', 'radio');
		$this->setFormAttribute('name', $this->name);
		if(!$this->fillable){
			return SelectiveColumn::renderRawsForm($formID);
		}else{
			$label = array_pop($this->option);
			$form  = SelectiveColumn::renderRawsForm($formID);
			$form .= '<input name="'.$this->name.'" type="radio" onchange="enableRadioFill(this, \''.$formID.'\')" />';
			$form .= $label;
			$form .= '<input name="'.$this->name.'" id="'.$formID.'_fill" disabled="disabled"/>';
			return $form;
		}
	}
	
	public function triggerGetJavaScript(){
		head_add_js('include/javascript/radio.column.js');
	}
	
	public function enableFill(){
		$this->fillable = true;
	}
	
	protected function getCheck($data){
		if($data != $this->data) $this->setFormAttribute('checked', '');
		else $this->setFormAttribute('checked', 'checked');
	}
}
?>
