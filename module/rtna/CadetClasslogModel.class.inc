<?php
class CadetClasslogModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_cadet_classlog';
	public $dropMode = 'rtna_cadet_activity_drop';
	
	function CadetClasslogModel($classlogID=null){
		$this->classlog = $this->none($classlogID, 'int');
		$this->classlog->isGridForm = false;
		$this->classlog->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
	}
	
	public function triggerSetParent($parentID){
		$this->classlog->data = $parentID;
	}
}
?>