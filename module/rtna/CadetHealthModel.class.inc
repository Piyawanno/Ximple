<?php
class CadetHealthModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_cadet_health';
	public $dropMode = 'rtna_cadet_health_drop';
	
	function CadetHealthModel($healthID=null){
		$this->health = $this->none($healthID, 'int');
		$this->health->isGridForm = false;
		$this->health->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
	}
	
	public function triggerSetParent($parentID){
		$this->health->data = $parentID;
	}
}
?>