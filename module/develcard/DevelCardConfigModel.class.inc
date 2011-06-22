<?php
class DevelCardConfigModel extends Model{
	function DevelCardConfigModel(){
		$option = develcard_get_permission_option();
		$this->develcard_access = $this->radio(tt('DevelCard report permission'), $option);
		$this->develcard_hight_color = $this->color('high priority color');
		$this->develcard_medium_color = $this->color('medium priority color');
		$this->develcard_low_color = $this->color('low priority color');
		$this->develcard_no_effect_color = $this->color('no-effect priority color');
		
		$this->develcard_type = $this->grid(tt('DevelCard Type'));
		$cardType = cc('develcard_type');
		$cardTypeName= Model::char(tt('type name'));
		if(is_array($cardType)){
			$cardTypeName->data = $cardType;
		}
		$this->develcard_type->append('develcard_type', $cardTypeName);
	}
}
?>
