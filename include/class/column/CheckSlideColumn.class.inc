<?php
require_once('CheckBoxColumn.class.inc');

class CheckSlideColumn extends CheckBoxColumn{
	function CheckSlideColumn($label, $option, $help=null){
		SelectiveColumn::SelectiveColumn($label, $option, $help);
		$this->setType('array');
	}
	
	public function triggerGetJavaScript(){
		head_add_js('include/javascript/checkslide.column.js');
		head_add_js('include/external/jquery-itoggle/jquery.ibutton.js');
		head_add_js('include/external/jquery-itoggle/jquery.easing.1.3.js');
		head_add_js('include/external/jquery-itoggle/jquery.metadata.js');
		head_add_css('include/external/jquery-itoggle/style/jquery.ibutton.css');
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$this->name;
		$this->checkSortable();
		$this->setFormAttribute('type', 'checkbox');
		$this->setFormAttribute('name', $this->name.'[]');
		$this->setFormAttribute('class', 'checkslide');
		$render = $this->renderRawsForm($formID);
		return $render;
	}
	
	protected function getCheck($data){
		if(is_array($this->data)){
			if(in_array($data, $this->data)){
				$this->setFormAttribute('checked', 'checked');
			}else{
				$this->setFormAttribute('checked', '');
			}
		}else{
			if($data == $this->data){
				$this->setFormAttribute('checked', 'checked');
			}else{
				$this->setFormAttribute('checked', '');
			}
		}
	}
	
	protected function renderRawsForm($formID){
		$id = $formID.'_'.$this->name;
		$this->setFormAttribute('style', 'border:none;');
		$render = '';
		foreach($this->option as $key => $value){
			$this->setFormAttribute('value', $key);
			$this->getCheck($key);
			$render .= '<div class="'.$this->itemClass.'">'.$this->imageTag;
			$render .= '<label for="'.$id.'_'.$key.'">'.$value.'</label>';
			$render .= '<input '.$this->renderFormAttribute().' id="'.$id.'_'.$key.'"/>';
			$render .= '</div>';
		}
		$render .= '<span id="info_'.$id.'"></span>';
		return $render;
	}
}
?>
