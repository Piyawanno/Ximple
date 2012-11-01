<?php
require_once('rtna.tool.inc');
require_once('CadetClassLogModel.class.inc');
class ClassLogModel extends Model{
	function ClassLogModel(){
		$this->lecture_class = $this->select(tt('class'), rtna_get_lectureClass_option());
		$this->class_time = $this->timestamp(tt('class time'));
		$this->class_log = $this->shortText(tt('class log'));
		$this->class_log->isList = true;
		$this->absense_cadet = $this->grid(tt('absense cadet'))->setModel(new CadetClassLogModel());
		$this->section = $this->section();
	}
}
?>