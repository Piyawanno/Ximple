<?php
class PeopleFileModel extends Model{
	function PeopleFileModel($informationID=null){
		$this->short_description = $this->title(tt('short description'));
		$this->file = $this->file('file', 'files/peoipleinfo/');
		$this->type = $this->none('', 'char');
		$this->type->isGridForm = false;
		$this->information = $this->none($informationID, 'int');
		$this->information->isGridForm = false;
	}
	
	public function triggerSetParent($parentID){
		$this->information->defaultData = $parentID;
	}
}
?>
