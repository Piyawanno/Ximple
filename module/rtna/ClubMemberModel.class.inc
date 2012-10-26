<?php
class ClubMemberModel extends Model{
	public $moduleName = 'rtna';
	public $tableName = 'rtna_club_member';
	public $dropMode = 'rtna_club_member_drop';
	
	function ClubMemberModel($clubID=null){
		$this->club = $this->none($clubID, 'int');
		$this->club->isGridForm = false;
		$this->club->isParent = true;

		$this->cadet = $this->select(tt('cadet'), rtna_get_rtna_cadet_option());
	}
	
	public function triggerSetParent($parentID){
		$this->club->data = $parentID;
	}
}
?>