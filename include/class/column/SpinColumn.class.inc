<?php
class SpinColumn extends ModelColumn{
	function SpinColumn($label, $min, $max, $step=1, $help=null){
		$this->setType('int');
		$this->label = $label;
		$this->max = $max;
		$this->min = $min;
		$this->step = $step;
		$this->help = $help;
		$this->setFormAtrribute('size', 8);
	}
	
	function renderForm($formID){
		head_add_css('include/external/jquery-spinbox/jquery.spinbox.css');
		head_add_js('include/external/jquery-spinbox/jquery.spinbox.js');
		$id = $formID.'_'.$this->name;
		$this->setFormAtrribute('name', $this->name);
		$this->setFormAtrribute('id', $id);
		$this->setFormAtrribute('value', $this->data);
		$render.= '<span id="info_'.$id.'"></span>';
		$render.= '
		<script>
			$("#'.$id.'").spinbox({
				min  : '.$this->min.',
				max  : '.$this->max.',
				step : '.$this->step.',
			});
		</script>';
		return $render;
	}
	
	function renderGridForm($formID){
		head_add_css('include/external/jquery-spinbox/jquery.spinbox.css');
		head_add_js('include/external/jquery-spinbox/jquery.spinbox.js');
		$id = $formID.'_'.$this->name;
		$this->setFormAtrribute('name', $this->name.'[]');
		$this->setFormAtrribute('class', $id);
		$this->setFormAtrribute('value', $this->data);
		$render.= '
		<script>
			$(".'.$id.'").spinbox({
				min  : '.$this->min.',
				max  : '.$this->max.',
				step : '.$this->step.',
			});
		</script>';
		return $render;
	}
}
?>
