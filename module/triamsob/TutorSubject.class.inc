<?php
include_once('triamsob.tool.inc');
include_once(ROOT_PATH.'include/class/Control.class.inc');
include_once(ROOT_PATH.'include/class/Model.class.inc');
include('TutorSubjectModel.class.inc');

class TutorSubject extends Control{
	function TutorSubject(){
		$this->moduleName = 'tutorsubject';
		$this->tableName = 'tutorsubject';
		$this->init(new TutorSubjectModel());
	}
	
	public function edit(){
		$this->formMeta->id = $this->moduleName;
		$this->formMeta->mode = 'triamsob_tutor_subject_save';
		$this->formMeta->title = tt('Update Tutor Subjects');
		document_set_path($this->formMeta->title);
		$clause = 'WHERE owner='.gg('id');
		$this->data[$this->id]['subject'] = db_select_single_column($this->tableName, 'subject', $clause);
		return $this->renderUpdateForm();
	}
	
	public function update(){
		$owner = (int) pp('owner');
		db_drop_many($this->tableName, 'owner='.$owner);
		$data = array('owner' => $owner);
		foreach(pp('subject') as $key => $value){
			$data['subject'] = (int) $value;
			db_insert($this->tableName, $data);
		}
	}
	
	public function createTable(){
		Control::createTable();
	}
}
?>
