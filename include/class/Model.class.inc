<?php
include_once('ModelColumn.class.inc');

abstract class Model{
	private $extendedObjBefore = array();
	private $extendedObjAfter = array();
	private $caegorized = false;
	
	public function getExtendedBefore($columnName){
		if(isset($this->extendedObjBefore[$columnName])){
			return $this->extendedObjBefore[$columnName];
		}else{
			return null;
		}
	}
	
	public function getExtendedAfter($columnName){
		if(isset($this->extendedObjAfter[$columnName])){
			return $this->extendedObjAfter[$columnName];
		}else{
			return null;
		}
	}
	
	public function hasCategory(){
		return $this->caegorized;
	}
	
	protected function extendBefore($beforeColumnName, $extendedColumnName){
		$this->extendedObjBefore[$beforeColumnName][] = $extendedColumnName;
	}
	
	protected function extendAfter($afterColumnName, $extendedColumnName){
		$this->extendedObjAfter[$afterColumnName][] = $extendedColumnName;
	}
	
	protected function drop($columnName){
		unset($this->$columnName);
	}
	
	public function section(){
		require_once('column/SectionColumn.class.inc');
		return new SectionColumn();
	}
	
	public function hidden($default=null, $type='char'){
		require_once('column/HiddenColumn.class.inc');
		return new HiddenColumn($default, $type);
	}
	
	public function owner(){
		include_once('column/OwnerColumn.class.inc');
		return new OwnerColumn();
	}
	
	public function char($label, $help=null){
		include_once('column/CharColumn.class.inc');
		return new CharColumn($label, $help);
	}
	
	public function title($label, $help=null){
		include_once('column/CharColumn.class.inc');
		$modelColumn = new CharColumn($label, $help);
		$modelColumn->isList = true;
		$modelColumn->isReachable = true;
		$modelColumn->isNotNull = true;
		return $modelColumn;
	}
	
	public function color($label, $help=null){
		include_once('column/ColorColumn.class.inc');
		return new ColorColumn($label, $help);
	}
	
	public function file($label, $path, $help=null){
		include_once('column/FileColumn.class.inc');
		return new FileColumn($label, $path, $help);
	}
	
	public function image($label, $path, $maxWidth=600, $help=null){
		include_once('column/ImageColumn.class.inc');
		return new ImageColumn($label, $path, $maxWidth, $help);
	}
	
	public function spin($label, $min, $max, $step=1, $help=null){
		include_once('column/SpinColumn.class.inc');
		return new SpinColumn($label, $min, $max, $step, $help);
	}
	
	public function password($label, $help=null){
		include_once('column/CharColumn.class.inc');
		$modelColumn = new CharColumn($label, $help);
		$modelColumn->setFormAttribute('type', 'password');
		return $modelColumn;
	}
	
	public function none($default=null, $type='char'){
		include_once('column/NoneColumn.class.inc');
		return new NoneColumn($label, $help);
	}
	
	public function category($module, $help=null){
		$this->caegorized = true;
		include_once('column/CategoryColumn.class.inc');
		return new CategoryColumn($module, $help);
	}
	
	public function fileSize($label, $help=null){
		include_once('column/FileSizeColumn.class.inc');
		return new FileSizeColumn($label, $help);
	}
	
	public function listDummy($label, $help=null){
		include_once('column/NoneColumn.class.inc');
		$modelColumn = NoneColumn($label, $help);
		$modelColumn->isDB = false;
		$modelColumn->isList = true;
		return $modelColumn;
	}
	
	public function email($label, $help=null){
		include_once('column/EmailColumn.class.inc');
		return new EmailColumn($label, $help);
	}
	
	public function now(){
		include_once('column/NowColumn.class.inc');
		return new NowColumn();
	}
	
	public function calendar($label, $help=null){
		include_once('column/CalendarColumn.class.inc');
		return new CalendarColumn($label, $help);
	}
	
	public function select($label, $option, $help=null){
		include_once('column/SelectColumn.class.inc');
		return new SelectColumn($label, $option, $help);
	}
	
	public function multiselect($label, $option, $help=null){
		include_once('column/SelectColumn.class.inc');
		$modelColumn = SelectColumn($label, $option, $help);
		$modelColumn->setType('array');
		$modelColumn->setFormAttribute('multiple', 'multiple');
		return $modelColumn;
	}
	
	public function radio($label, $option, $help=null){
		include_once('column/RadioColumn.class.inc');
		return new RadioColumn($label, $option, $help);
	}
	
	public function enable($label, $help=null){
		include_once('column/RadioColumn.class.inc');
		$modelColumn = new RadioColumn($label, $option, $help);
		$modelColumn->setType('int');
		$modelColumn->option = array(0 => tt('disable'), 1 => tt('enable'));
		return $modelColumn;
	}
	
	public function checkbox($label, $option, $help=null){
		include_once('column/CheckBoxColumn.class.inc');
		return new CheckBoxColumn($label, $option, $help);
	}
	
	public function group($label, $help=null){
		include_once('column/GroupColumn.class.inc');
		return new GroupColumn($label, $help);
	}
	
	public function checkedit($label, $option, $help=null){
		include_once('column/CheckEditColumn.class.inc');
		return new CheckEditColumn($label, $option, $help);
	}
	
	public function timeInterval($label, $interval, $help=null){
		include_once('column/TimeIntervalColumn.class.inc');
		return new TimeIntervalColumn($label, $interval, $help);
	}
	
	public function text($label, $help=null){
		include_once('column/TextColumn.class.inc');
		return new TextColumn($label, $help);
	}
	
	public function shortText($label, $help=null){
		include_once('column/TextColumn.class.inc');
		$modelColumn = new TextColumn($label, $help);
		$modelColumn->setType('shorttext');
		$modelColumn->setFormAttribute('class', 'shorttext');
		return $modelColumn;
	}
	
	public function plain($label, $help=null){
		include_once('column/PlainTextColumn.class.inc');
		return new PlainTextColumn($label, $help);
	}
	
	public function autoComplete($label, $ajaxMode, $help=null){
		include_once('column/AutoCompleteColumn.class.inc');
		return new AutoCompleteColumn($label, $ajaxMode, $help);
	}
	
	public function user($label, $help=null){
		include_once('column/AutoCompleteColumn.class.inc');
		$modelColumn = new AutoCompleteColumn($label, 'userinfo_get_ajax_name', $help);
		$modelColumn->isNotNull = true;
		$modelColumn->help = $help.tt('Type beginning letters of the user name. ');
		$modelColumn->help.= tt('The full name will be automatically completed. ');
		$modelColumn->help.= tt('Multiple names are possible using comma.');
		return $modelColumn;
	}
	
	public function imageLoader($label, $path){
		include_once('column/ImageLoaderColumn.class.inc');
		return new ImageLoaderColumn($label, $path);
	}
	
	public function grid($label, $help=null){
		include_once('column/GridColumn.class.inc');
		return new GridColumn($label, $help);
	}
}
?>
