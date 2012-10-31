<?php
class CadetBedroomModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_cadet_bedroom';
	public $dropMode = 'rtna_cadet_bedroom_drop';
	
	function CadetBedroomModel($bedroomID=null){
		$this->bedroom = $this->none($bedroomID, 'int');
		$this->bedroom->isGridForm = false;
		$this->bedroom->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
	}
	
	public function triggerSetParent($parentID){
		$this->bedroom->data = $parentID;
	}
}
?>