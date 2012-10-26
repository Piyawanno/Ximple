<?php
class CadetClassLogModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_cadet_classLog';
	public $dropMode = 'rtna_cadet_classLog_drop';
	
	function CadetClassLogModel($classLogID=null){
		$this->classLog = $this->none($classLogID, 'int');
		$this->classLog->isGridForm = false;
		$this->classLog->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
	}
	
	public function triggerSetParent($parentID){
		$this->classLog->data = $parentID;
	}
}
?>