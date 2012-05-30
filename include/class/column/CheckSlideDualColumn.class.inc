<?php
require_once('CheckSlideColumn.class.inc');

class CheckSlideDualColumn extends CheckSlideColumn{
	function CheckSlideDualColumn($label, $option, $help=null){
		SelectiveColumn::SelectiveColumn($label, $option, $help);
		$this->setType('int');
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$this->name;
		$this->checkSortable();
		$this->setFormAttribute('type', 'checkbox');
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('class', 'checkslidedual');
		$render = $this->renderRawsForm($formID);
		return $render;
	}
	
	protected function renderRawsForm($formID){
		$id = $formID.'_'.$this->name;
		$this->setFormAttribute('style', 'border:none;');
		if($this->data == 1) $this->setFormAttribute('checked', 'checked');
		else $this->setFormAttribute('checked', '');
		$render  = '<div class="'.$this->itemClass.'">'.$this->imageTag;
		$render .= '<label for="'.$id.'"></label>';
		$render .= '<input '.$this->renderFormAttribute().' id="'.$id.'" value="1"/>';
		$render .= '</div>';
		$render .= '<span id="info_'.$id.'"></span>';
		$render .=
			'<script>
				$("#'.$id.'").iButton({
					labelOn : "'.$this->option[1].'",
					labelOff : "'.$this->option[0].'"
				});
			</script>';
		return $render;
	}
}
?>
