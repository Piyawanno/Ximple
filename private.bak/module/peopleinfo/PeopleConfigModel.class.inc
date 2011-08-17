<?php
class PeopleConfigModel extends Model{
	function PeopleConfigModel(){
		$this->data_type = $this->grid(tt('Data Type'));
		$type = cc('peopleinfo_data_type');
		$typeName= Model::char(tt('type name'));
		if(is_array($type)){
			$typeName->data = $type;
		}
		$this->data_type->append('peopleinfo_data_type', $typeName);
	}
}
?>
