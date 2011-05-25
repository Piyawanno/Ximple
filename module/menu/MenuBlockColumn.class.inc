<?php
require_once(ROOT_PATH.'include/class/column/SelectColumn.class.inc');

class MenuBlockColumn extends SelectColumn{
	function MenuBlockColumn(){
		SelectColumn::SelectColumn(tt('includes Block'), array());
		$this->setType('int');
		$p = tt('Use <a href="%s">block interface</a> for Block configuration.');
		$this->help = sprintf($p, SECTION_URI.Q.'block');
	}
	
	public function renderForm($formID){
		if(cc('menu_include_block')){
			return SelectColumn::renderForm($formID);
		}else{
			return $this->renderAdHidden($formID);
		}
	}
	
	public function triggerInsertForm(){
		$this->getBlock();
	}
	
	public function triggerUpdateForm(){
		$this->getBlock();
	}
	
	private function getBlock(){
		if(cc('menu_include_block')){
			$this->option = db_select_single_column('block', 'title', 'WHERE section='.SECTION, true);
			$this->option[0] = cc('None');
			ksort($this->option);
		}
	}
	
	private function renderAsHidden($formID){
		require_once(ROOT_PATH.'include/class/column/HiddenColumn.class.inc');
		$hidden = new Hidden($this->data, 'int');
		return $hidden->renderForm($formID);
	}
}
?>
