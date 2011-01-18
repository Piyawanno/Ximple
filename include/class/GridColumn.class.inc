<?php
/// This class is a container for other ModelColumns.
/// It does not represent a column of database table.

class GridColumn extends ModelColumn{
	private $memberColumn;
	private $allowedGridForm = array(
		'char',
		'email',
		'select',
		'file',
		'color',
		'uri'
	);
	
	function GridColumn($label, $help=null){
		$this->type = 'array';
		$this->form = 'grid';
		$this->help = $help;
		$this->label = $label;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
	}
	
	public function append($memberName, $memberModel){
		if(!in_array($memberModel->form, $this->allowedGridForm)){
			if(state_is_develop()){
				notify_add_error(sprintf(tt('Grid is not allowed to contain form : %s.'), $memberModel->form));
			}
		}else{
			$memberModel->isForm = false;
			$this->memberColumn[$memberName] = $memberModel;
		}
	}
	
	public function getMember(){
		return $this->memberColumn;
	}
}
?>
