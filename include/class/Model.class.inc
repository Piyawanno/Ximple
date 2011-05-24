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
	
	public function file($label, $path, $help=null){
		$modelColumn = new ModelColumn;
		
		return $modelColumn;
	}
	
	public function title($label, $help=null){
		include_once('column/CharColumn.class.inc');
		$modelColumn = CharColumn($label, $help);
		$modelColumn->isList = true;
		$modelColumn->isReachable = true;
		$modelColumn->isNotNull = true;
		return $modelColumn;
	}
	
	public function listDummy($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->isForm = false;
		$modelColumn->isDB = false;
		$modelColumn->isList = true;
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		return $modelColumn;
	}

	public function spin($label, $min, $max, $step=1, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'int';
		$modelColumn->form = 'spin';
		$modelColumn->label = $label;
		$modelColumn->max = $max;
		$modelColumn->min = $min;
		$modelColumn->step = $step;
		$modelColumn->help = $help;
		return $modelColumn;
	}
	
	public function password($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'char';
		$modelColumn->form = 'password';
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		return $modelColumn;
	}
	
	public function email($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'char';
		$modelColumn->form = 'email';
		$modelColumn->isNotNull = true;
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		return $modelColumn;
	}
	
	public function none($default=null, $type='char'){
		$modelColumn = new ModelColumn;
		$modelColumn->type = $type;
		$modelColumn->form = 'none';
		$modelColumn->defaultData = $default;
		$modelColumn->data = $default;
		return $modelColumn;
	}
	
	public function now(){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'timestamp';
		$modelColumn->form = 'hidden';
		$modelColumn->defaultData = NOW;
		$modelColumn->data = NOW;
		return $modelColumn;
	}
	
	public function radio($label, $option, $help=null){
		$modelColumn = Model::selective($label, $option, $help);
		$modelColumn->form = 'radio';
		return $modelColumn;
	}
	
	public function checkbox($label, $option, $help=null){
		$modelColumn = Model::selective($label, $option, $help);
		$modelColumn->form = 'checkbox';
		$modelColumn->type = 'array';
		return $modelColumn;
	}
	
	public function checkedit($label, $option, $help=null){
		$modelColumn = Model::selective($label, $option, $help);
		$modelColumn->form = 'checkedit';
		$modelColumn->type = 'array';
		return $modelColumn;
	}
	
	public function select($label, $option, $help=null){
		$modelColumn = Model::selective($label, $option, $help);
		$modelColumn->form = 'select';
		return $modelColumn;
	}
	
	public function multiselect($label, $option, $help=null){
		$modelColumn = Model::selective($label, $option, $help);
		$modelColumn->form = 'multiselect';
		$modelColumn->type = 'array';
		return $modelColumn;
	}
	
	public function calendar($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'timestamp';
		$modelColumn->form = 'calendar';
		$modelColumn->defaultData = NOW;
		$modelColumn->data = NOW;
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		return $modelColumn;
	}
	
	public function text($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'text';
		$modelColumn->form = 'text';
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		return $modelColumn;
	}
	
	public function shortText($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'shorttext';
		$modelColumn->form = 'shorttext';
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		return $modelColumn;
	}
	
	public function plain($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'shorttext';
		$modelColumn->form = 'plain';
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		return $modelColumn;
	}
	
	public function group($label, $help=null){
		include_once('GroupColumn.class.inc');
		return new GroupColumn($label, $help);
	}
	
	public function user($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'char';
		$modelColumn->form = 'autocomplete';
		$modelColumn->label = $label;
		$modelColumn->isNotNull = true;
		$modelColumn->help = $help.tt('Type beginning letters of the user name. ');
		$modelColumn->help.= tt('The full name will be automatically completed. ');
		$modelColumn->help.= tt('Multiple names are possible using comma.');
		$modelColumn->ajaxMode = 'userinfo_get_ajax_name';
		return $modelColumn;
	}
	
	public function autoComplete($label, $ajaxMode, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'shorttext';
		$modelColumn->form = 'autocomplete';
		$modelColumn->label = $label;
		$modelColumn->ajaxMode = $ajaxMode;
		return $modelColumn;
	}
	
	public function enable($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'int';
		$modelColumn->form = 'radio';
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		$modelColumn->option = array(0 => tt('disable'), 1 => tt('enable'));
		return $modelColumn;
	}
	
	public function image($label, $path, $maxWidth=600, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'char';
		$modelColumn->form = 'file';
		$modelColumn->label = $label;
		$modelColumn->help = tt('Image must be only .png or .jpeg or .jpg. ');
		$modelColumn->help.= sprintf(tt('For image wider than %dpx, it will be automatically resized.'), $maxWidth);
		$modelColumn->path = $path;
		$modelColumn->isImage = true;
		$modelColumn->isOrderable = false;
		$modelColumn->maxWidth = $maxWidth;
		return $modelColumn;
	}
	
	public function color($label, $help=null){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'char';
		$modelColumn->form = 'color';
		$modelColumn->label = $label;
		$modelColumn->help = $help;
		$modelColumn->defaultData = "#5555ee";
		$modelColumn->data = "#5555ee";
		return $modelColumn;
	}
	
	public function imageLoader($label, $path){
		$modelColumn = new ModelColumn;
		$modelColumn->type = 'char';
		$modelColumn->form = 'imageloader';
		$modelColumn->label = $label;
		$modelColumn->path = $path;
		$modelColumn->help = tt('Click on image to upload or change image.');
		return $modelColumn;
	}
	
	public function timeInterval($label, $interval, $help=null){
		include_once('TimeIntervalColumn.class.inc');
		return new TimeIntervalColumn($label, $interval, $help);
	}
	
	public function grid($label, $help=null){
		include_once('GridColumn.class.inc');
		return new GridColumn($label, $help);
	}
	
	public function category($module, $help=null){
		$this->caegorized = true;
		include_once('CategoryColumn.class.inc');
		return new CategoryColumn($module, $help);
	}
	
	public function fileSize($label, $help=null){
		include_once('FileSizeColumn.class.inc');
		return new FileSizeColumn($label, $help);
	}
	
	private function selective($label, $option, $help){
		include_once('SelectiveColumn.class.inc');
		$modelColumn = new SelectiveColumn($label, $option, $help);
		return $modelColumn;
	}
}
?>
