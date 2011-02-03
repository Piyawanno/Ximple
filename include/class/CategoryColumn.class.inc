<?php
class CategoryColumn extends ModelColumn{
	private $module;
	
	function CategoryColumn($module, $help=null){
		$this->type = 'int';
		$this->form = 'select';
		$this->label = tt('category');
		$this->help = $help;
		$this->module = $module;
		$this->option = array();
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
		if(isset($data[$this->data])){
			$this->data = $data[$this->data];
			$reference = $this->data['category'];
			$this->data = translate_content($this->data, 'category', $this->data['id']);
			$this->data['reference'] = $reference;
		}
	}
	
	private function getSelection(){
		$clause = "WHERE (mode='".$this->module."' AND section=".SECTION.")";
		$this->option = db_select_single_column('category', 'category', $clause);
	}
}
?>
