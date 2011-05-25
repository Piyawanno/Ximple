<?php
class SpinColumn extends ModelColumn{
	function SpinColumn($label, $min, $max, $step=1, $help=null){
		$this->setType('int');
		$this->label = $label;
		$this->max = $max;
		$this->min = $min;
		$this->step = $step;
		$this->help = $help;
		$this->setFormAttribute('size', 8);
	}
	
	function renderForm($formID){
		head_add_css('include/external/jquery-spinbox/jquery.spinbox.css');
		head_add_js('include/external/jquery-spinbox/jquery.spinbox.js');
		$id = $formID.'_'.$this->name;
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('id', $id);
		$this->setFormAttribute('value', $this->data);
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
		$this->setFormAttribute('name', $this->name.'[]');
		$this->setFormAttribute('class', $id);
		$this->setFormAttribute('value', $this->data);
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
