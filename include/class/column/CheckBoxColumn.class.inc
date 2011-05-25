<?php
require_once('SelectiveColumn.class.inc');
class CheckBoxColumn extends SelectiveColumn{
	function CheckBoxColumn($label, $option, $help=null){
		SelectiveColumn::SelectiveColumn($label, $option, $help);
		$this->setType('array');
	}
	
	public function renderForm($formID){
		head_add_js('include/javascript/checkboxcolumn.js');
		$this->checkSortable();
		$this->divisionClass = 'checkbox_list';
		$this->setFormAtrribute('type', 'checkbox');
		$this->setFormAtrribute('name', $this->name.'[]');
		$render = SelectiveForm::renderRawsForm($formID);
		if(count($this->option) > 1){
			$render .= '<p><a href="javascript:checkAllCheckBox(\''.$this->name.'\')">'.tt('check all').'</a> | ';
			$render .= '<a href="javascript:checkNoneCheckBox(\''.$this->name.'\')">'.tt('check none').'</a></p>';
		}
	}
	
	protected function getCheck($data){
		if(is_array($this->data) and in_array($data, $this->data)){
			$this->setFormAtrribute('checked', 'checked');
		}else{
			$this->setFormAtrribute('checked', '');
		}
	}
}
?>
