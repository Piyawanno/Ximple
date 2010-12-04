<?php
class CategoryColumn extends ModelColumn{
	private $module;
	
	function CategoryColumn($module, $help=null){
		$this->type = 'int';
		$this->form = 'select';
		$this->label = tt('category');
		$this->help = $help;
		$this->module = $module;
		$this->selection = array();
	}
	
	public function triggerInsertForm(){
		$this->getSelection();
	}
	
	public function triggerUpdateForm(){
		$this->getSelection();
	}
	
	public function triggerSelect(){
		$clause = 'WHERE id='.$this->data;
		$data = db_select('category', array('id', 'category', 'description', 'pic'), $clause);
		$this->data = $data[$this->data];
	}
	
	private function getSelection(){
		$clause = "WHERE (mode='".$this->module."' AND section=".SECTION.")";
		$this->selection = db_select_single_column('category', 'category', $clause);
	}
}
?>
