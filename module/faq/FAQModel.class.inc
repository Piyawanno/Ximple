<?php
class FAQModel extends Model{
	function FAQModel(){
		$this->owner = $this->owner();
		$this->question = $this->title(tt('question'));
		$this->question->isList = true;
		$this->category = $this->category('faq');
		
		$option = array(
			0 => tt('draft'),
			1 => tt('publish'),
		);
		$this->status = $this->select(tt('status'), $option);
		$this->answer = $this->text(tt('answer'));
		$this->section = $this->section();
	}
}
?>
