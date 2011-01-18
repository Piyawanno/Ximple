<?php
/// This class is a container for other ModelColumns.
/// It does not represent a column of database table.

class GridColumn extends ModelColumn{
	private $memberColumn;
	private $memberDataCount;
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
			$memberModel->isMultipleInsert = true;
			$memberModel->isForm = false;
			$this->memberColumn[$memberName] = $memberModel;
		}
	}
	
	public function getMember(){
		$this->checkMemberData();
		$this->getMemberData();
		return $this->memberColumn;
	}
	
	private function checkMemberData(){
		$dataCount = array();
		$dataOK = true;
		foreach($this->memberColumn as $key => $value){
			if(is_array($value->data)){
				$dataCount[] = count($value->data);
			}else{
				$dataCount[] = null;
			}
		}
		if(count($dataCount)){
			foreach($dataCount as $key => $value){
				if($value != $dataCount[0]){
					notify_add_warning(sprintf(tt('Data for %s is corrupted!'), $this->label));
					$dataOK = false;
					break;
				}
			}
		}
		if($dataOK) $this->memberDataCount = $dataCount[0];
	}
	
	private function getMemberData(){
		$this->data = array();
		for($i=0;$i<$this->memberDataCount;$i++){
			foreach($this->memberColumn as $key => $value){
				if(is_array($value->data)){
					$this->data[$i][$key] = $value->data[$i];
				}
			}
		}
	}
}
?>
