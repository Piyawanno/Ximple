<?php
class CadetExamModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_cadet_exam';
	public $dropMode = 'rtna_cadet_exam_drop';
	
	function CadetExamModel($examID=null){
		$this->exam = $this->none($examID, 'int');
		$this->exam->isGridForm = false;
		$this->exam->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
		$this->point = $this->spin(tt('point'), 0);
		
	}
	
	public function triggerSetParent($parentID){
		$this->exam->data = $parentID;
	}
}
?>