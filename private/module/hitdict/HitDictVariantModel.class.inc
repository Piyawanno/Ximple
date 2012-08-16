<?php
class HitDictVariantModel extends Model{
	public $moduleName = 'hitdict';
	public $tableName = 'hitdict_variant';
	public $dropMode = 'hitdict_variant_drop';
	
	function HitDictVariantModel($hid=null){
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
