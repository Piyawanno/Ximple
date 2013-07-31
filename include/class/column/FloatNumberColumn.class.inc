<?php
class FloatNumberColumn extends ModelColumn{
	private $mainData;
	private $subData;
	private $unitLabel;
	
	function FloatNumberColumn($label, $unitLabel, $help=null){
		$this->setType('real');
		$this->label = $label;
		$this->unitLabel = $unitLabel;
		$this->help = $help;
	}
	
	public function triggerGetJavaScript(){
		head_add_css('include/external/jquery-spinbox/jquery.spinbox.css');
		head_add_js('include/external/jquery-spinbox/jquery.spinbox.js');
		head_add_js('include/javascript/floatnumber.column.js');
	}
	
	public function renderForm($formID){
		$this->prepareData();
		$id = $formID.'_'.$this->name;
		
		$this->setFormAttribute('type', 'hidden');
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('class', 'floatnumber');
		$this->setFormAttribute('id', $id);
		$render = '<input '.$this->renderFormAttribute().'/>';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('name', $this->name.'_main');
		$this->setFormAttribute('id', $id.'_main');
		$this->setFormAttribute('value', (int) $this->mainData);
		$this->setFormAttribute('class', 'floatnumber_main');
		$this->setFormAttribute('size', 5);
		$render.= '<input '.$this->renderFormAttribute().'/>.';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('name', $this->name.'_sub');
		$this->setFormAttribute('id', $id.'_sub');
		$this->setFormAttribute('value', (int) $this->subData);
		$this->setFormAttribute('class', 'floatnumber_sub');
		$this->setFormAttribute('size', 2);
		$render.= '<input '.$this->renderFormAttribute().'/> '.$this->unitLabel;
		$render.= '<span id="info_'.$id.'"></span>';
		return $render;
	}
	
	public function renderGridForm($formID){
		$this->prepareData();
		$id = $formID.'_'.$this->name;
		
		$this->setFormAttribute('type', 'hidden');
		$this->setFormAttribute('name', $this->name.'[]');
		$this->setFormAttribute('class', 'floatnumber');
		$render = '<input '.$this->renderFormAttribute().'/>';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('name', $this->name.'_main[]');
		$this->setFormAttribute('value', (int) $this->mainData);
		$this->setFormAttribute('class', 'floatnumber_main');
		$this->setFormAttribute('size', 5);
		$render.= '<input '.$this->renderFormAttribute().'/>.';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('name', $this->name.'_sub[]');
		$this->setFormAttribute('value', (int) $this->subData);
		$this->setFormAttribute('class', 'floatnumber_sub');
		$this->setFormAttribute('size', 5);
		$render.= '<input '.$this->renderFormAttribute().'/>'.$this->unitLabel;
		return $render;
	}
	
	private function prepareData(){
		$this->data = (float) $this->data;
		$this->mainData = (int) $this->data;
		$this->subData = (int)(($this->data - $this->mainData)*100);
	}
}
?>
