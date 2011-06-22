<?php
class ResolverModel extends Model{
	public $moduleName = 'develcard';
	public $tableName = 'develcard_resolver';
	public $dropMode = 'develcard_drop_resolver';
	
	function ResolverModel($develcardID=null){
		$option = userinfo_get_login_name_by_role('develcard_resolver');
		$this->resolver = $this->select(tt('user'), $option);
		$this->develcard = $this->none($develcardID, 'int');
		$this->develcard->isGridForm = false;
		$this->develcard->isParent = true;
	}
	
	public function triggerSetParent($parentID){
		$this->develcard->data = $parentID;
	}
}
?>
