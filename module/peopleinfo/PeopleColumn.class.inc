<?php
require_once(ROOT_PATH.'include/class/column/SelectColumn.class.inc');
require_once(ROOT_PATH.'include/class/column/HiddenColumn.class.inc');

class PeopleColumn extends SelectColumn{
	private $isSelect;
	
	function PeopleColumn(){
		SelectColumn::SelectColumn(tt('user'), array());
		$this->isList = true;
		$this->isUser = true;
		$this->isOrderable = false;
		$this->isReachable = true;
		$this->listMode = 'peopleinfo';
	}
	
	public function renderForm($formID){	
		if($this->isSelect){
			return SelectColumn::renderForm($formID);
		}else{
			$hidden = new HiddenColumn($this->defaultData, 'int');
			return $hidden->renderForm($formID);
		}
	}
	
	public function triggerInsertForm(){
		$this->isSelect = true;
		$this->option = peopleinfo_get_unprocessed_user();
		head_add_js_var('peopleUserNumber', count($this->option));
	}
	
	public function triggerUpdateForm(){
		$this->isSelect = false;
		$this->isFormLabel = false;
		head_add_js_var('peopleUserNumber', 1);
	}
}
?>
