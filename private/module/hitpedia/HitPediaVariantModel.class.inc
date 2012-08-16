<?php
class HitPediaVariantModel extends Model{
	public $moduleName = 'hitpedia';
	public $tableName = 'hitpedia_variant';
	public $dropMode = 'hitpedia_variant_drop';
	
	function HitPediaVariantModel($hid=null){
		$this->variant = $this->char(tt('Variant'));
		
		$this->hid = $this->none($hid, 'int');
		$this->hid->isGridForm = false;
		$this->hid->isParent = true;
	}
	
	public function triggerSetParent($hid){
		$this->hid->data = $hid;
	}
	
}
?>
