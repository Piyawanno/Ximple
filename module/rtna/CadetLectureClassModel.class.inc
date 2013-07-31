<?php
class CadetLectureClassModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_cadet_lectureClass';
	public $dropMode = 'rtna_cadet_lectureClass_drop';
	
	function CadetLectureClassModel($lectureClassID=null){
		$this->lectureClass = $this->none($lectureClassID, 'int');
		$this->lectureClass->isGridForm = false;
		$this->lectureClass->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
	}
	
	public function triggerSetParent($parentID){
		$this->lectureClass->data = $parentID;
	}
}
?>