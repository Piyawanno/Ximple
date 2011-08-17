<?php
class DataReportModel extends Model{
	function DataReportModel(){
		$type = cc('peopleinfo_data_type');
		$this->shown_type = $this->checkbox(tt('shown type'), $type);
		$this->shown_type->data = array_keys($type);
		$option = array(
			'and' => tt('AND'),
			'or' => tt('OR'),
		);
		$this->and_or = $this->select(tt('AND/OR'), $option);
		$this->condition = $this->grid(tt('search condition'));
		$this->condition->append('data_type', Model::select(tt('data type'), $type));
		$option = array(
			'='  => '=',
			'!=' => '!=',
			'LIKE' => 'LIKE',
			'>=' => '>=',
			'>'  => '>',
			'<'  => '<',
			'<=' => '<=',
		);
		$this->condition->append('condition', Model::select(tt('condition'), $option));
		$this->condition->append('data', Model::title(tt('data')));
	}
}
?>
