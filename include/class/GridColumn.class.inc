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
	
	function GridColumn($help=null){
		$this->type = 'array';
		$this->form = 'grid';
		$this->help = $help;
		$this->isMultipleInsert = true;
		$this->memberColumn = array();
		$this->isDB = false;
	}
	
	public function append($member){
		if(!in_array($memer->form, $this->allowedGridForm)){
		}else{
			$this->memberColumn[] = $member;
		}
	}
	
	public function getMember(){
		return $this->memberColumn;
	}
}
?>
