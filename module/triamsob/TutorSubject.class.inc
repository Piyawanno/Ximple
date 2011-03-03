<?php
execute_add_class('triamsob', 'TutorSubject');
include('TutorSubjectModel.class.inc');

class TutorSubject extends Control{
	function TutorSubject(){
		$this->moduleName = 'tutorsubject';
		$this->tableName = 'tutorsubject';
		$this->setAdmin('triamsob_tutor');
		$this->addAction('triamsob_tutor_subject_edit', 'edit');
		$this->addAction('triamsob_tutor_subject_save', 'update');
		$this->init(new TutorSubjectModel($this->getOwnerID()));
	}
	
	public function edit(){
		$this->formMeta->id = $this->moduleName;
		$this->formMeta->mode = 'triamsob_tutor_subject_save';
		$this->formMeta->title = tt('Update Tutor Subjects');
		document_set_path(tt('User-Profile'), 'profile');
		document_set_path($this->formMeta->title);
		$clause = 'WHERE owner='.gg('id');
		$this->data[$this->id]['subject'] = db_select_single_column($this->tableName, 'subject', $clause);
		return $this->renderUpdateForm();
	}
	
	public function update(){
		print_r(pp());
		$owner = (int) pp('owner');
		db_drop_many($this->tableName, 'owner='.$owner);
		$data = array('owner' => $owner);
		foreach(pp('subject') as $key => $value){
			$data['subject'] = (int) $value;
			db_insert($this->tableName, $data);
		}
		execute_set_db();
		document_set_redirect('triamsob_tutor_subject_edit/'.pp('owner'));
	}
	
	public function createTable(){
		Control::createTable();
	}
	
	public function prepareMethod($method){
	}
	
	private function getOwnerID(){
		if(gg('id')) return gg('id');
		else return USER_ID;
	}
}
?>
