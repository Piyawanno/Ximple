<?php
class TextColumn extends ModelColumn{
	function TextColumn($label, $help=null){
		$this->setType('text');
		$this->label = $label;
		$this->help = $help;
		$this->isAllowedTranslate = true;
		$this->setFormAttribute('class', 'text');
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$this->name;
		head_add_css('include/external/cleditor/jquery.cleditor.css');
		$this->prepareEditor();
		$this->addJS();
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('id', $id);
		$this->setFormAttribute('style', 'width:100%');
		$this->setFormAttribute('rows', 20);
		$render = '<textarea '.$this->renderFormAttribute().'>'.$this->data.'</textarea>';
		$render.= '<span id="info_'.$id.'"></span>';
		return $render;
	}
	
	private function prepareEditor(){
		$smileyFolder  = ROOT_PATH.'files/smiley/';
		if(!is_dir($smileyFolder)) mkdir($smileyFolder);
		$smileyFolder .= SECTION.'/';
		if(!is_dir($smileyFolder)){
			mkdir($smileyFolder);
			$cleFolder = ROOT_PATH.'include/external/cleditor/images/icons/';
			io_copy_directory($cleFolder, $smileyFolder);
		}
		$iconArray = io_get_directory_entry($smileyFolder);
		foreach($iconArray as $key => $value){
			$iconArray[$key] = ROOT_URI.'files/smiley/'.SECTION.'/'.$value;
		}
		head_add_js_array('iconArray', $iconArray);
	}
	
	private function addJS(){
		head_add_js('include/external/cleditor/jquery.cleditor.js');
		head_add_js('include/external/cleditor/jquery.cleditor.advancedtable.min.js');
		head_add_js('include/external/cleditor/jquery.cleditor.icon.js');
		head_add_js('include/external/cleditor/jquery.cleditor.code.js');
		head_add_js('include/external/cleditor/jquery.cleditor.quote.js');
		head_add_js('include/external/cleditor/jquery.cleditor.advancedimage.js');
		head_add_js('include/javascript/textcolumn.js');
	}
}
?>
